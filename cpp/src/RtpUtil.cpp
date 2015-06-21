/*
 * RtpUtil.cpp
 *
 *  Created on: 2013-10-31
 *      Author: walter
 */

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "srtp.h"


/*
refer to
https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
http://www-mmsp.ece.mcgill.ca/documents/audioformats/wave/wave.html

<WAVE-form> → RIFF('WAVE'
                   <fmt-ck>            // Format
                   [<fact-ck>]         // Fact chunk
                   [<cue-ck>]          // Cue points
                   [<playlist-ck>]     // Playlist
                   [<assoc-data-list>] // Associated data list
                   <wave-data> )       // Wave data

Format Code PreProcessor Symbol Data
0x0001  WAVE_FORMAT_PCM PCM
0x0003  WAVE_FORMAT_IEEE_FLOAT  IEEE float
0x0006  WAVE_FORMAT_ALAW    8-bit ITU-T G.711 A-law
0x0007  WAVE_FORMAT_MULAW   8-bit ITU-T G.711 µ-law
0xFFFE  WAVE_FORMAT_EXTENSIBLE  Determined by SubFormat

*/
using namespace std;
char databuf[2048];

/*
wFormatTag    2   WAVE_FORMAT_EXTENSIBLE
nChannels    2  Nc
nSamplesPerSec   4  F
nAvgBytesPerSec  4  F * M * Nc
nBlockAlign  2  M * Nc
wBitsPerSample   2  8 * M
cbSize   2  Size of the extension: 22
wValidBitsPerSample  2  at most 8 * M
dwChannelMask    4  Speaker position mask: 0
SubFormat    16 GUID (first two bytes are the data format code)
 * */
struct wav_fmt_chunk
{
    uint8_t chunk_id[4];
    uint32_t chunk_size;
    uint16_t fmt_code;
    uint16_t channel_count;
    uint32_t sample_per_sec;
    uint32_t avg_bytes_per_sec;
    uint16_t block_align;
    uint16_t bits_per_sample;
    uint16_t extension_size;
//    uint16_t valid_bits_per_sample;
//    uint32_t speaker_pos_mask;
//    uint8_t sub_fmt[16];
};

struct wav_fact_chunk
{
    uint8_t chunk_id[4];
    uint32_t chunk_size;
    uint32_t sample_length;
};

struct wav_data_chunk
{
    uint8_t chunk_id[4];
    uint32_t chunk_size;
    uint8_t* chunk_data;
    uint8_t chunk_pad;
};

struct wav_file_struct
{
    uint8_t riff_flag[4];
    uint32_t wav_size;
    uint8_t wav_flag[4];
    wav_fmt_chunk fmt_chunk;
    wav_fact_chunk fact_chunk;
    wav_data_chunk data_chunk;
};


int read_wav_file(char* wav_file);

int rtp_util_test(int argc, char* argv[]) {
    return read_wav_file("../../handbook/audio/8.wav");
}

int read_wav_file(char*  wav_file_name) {
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;

    pFile = fopen(wav_file_name, "rb");
    if (pFile == NULL) {
        fputs("File error", stderr);
        exit(1);
    }

    // obtain file size:
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc(sizeof(char) * lSize);
    if (buffer == NULL) {
        fputs("Memory error", stderr);
        exit(2);
    }

    // copy the file into the buffer:
    printf("%s's size is %d\n", wav_file_name, lSize);
    result = fread(buffer, 1, lSize, pFile);
    if (result != lSize) {
        fputs("Reading error", stderr);
        exit(3);
    }

    wav_file_struct wav_file;
    memcpy((void*)&wav_file.riff_flag, buffer, 4);
    printf("file head: %s\n", wav_file.riff_flag);
    /* the whole file is now loaded in the memory buffer. */

    memcpy((void*)&wav_file.wav_size, buffer+4, 4);
    printf("wav size: %d\n", wav_file.wav_size);

    memcpy((void*)&wav_file.wav_flag, buffer+8, 4);
    printf("wav flag: %s\n", wav_file.wav_flag);

    memcpy((void*)&wav_file.fmt_chunk.chunk_id, buffer+12, 4);
    printf("wav fmt chunk id: %s\n", wav_file.fmt_chunk.chunk_id);

    memcpy((void*)&wav_file.fmt_chunk.chunk_size, buffer+16, 4);
    printf("wav fmt chunk size: %d\n", wav_file.fmt_chunk.chunk_size);

    memcpy((void*)&wav_file.fmt_chunk.fmt_code, buffer+20, 2);
    printf("wav fmt code: %d //7:PCMU\n", wav_file.fmt_chunk.fmt_code);

    memcpy((void*)&wav_file.fmt_chunk.channel_count, buffer+22, 2);
    printf("wav fmt channel count: %d\n", wav_file.fmt_chunk.channel_count);

    memcpy((void*)&wav_file.fmt_chunk.sample_per_sec, buffer+24, 4);
    printf("wav fmt sample rate per second: %d\n", wav_file.fmt_chunk.sample_per_sec);

    memcpy((void*)&wav_file.fmt_chunk.avg_bytes_per_sec, buffer+28, 4);
    printf("wav fmt avg_bytes_per_sec: %d\n", wav_file.fmt_chunk.avg_bytes_per_sec);

    memcpy((void*)&wav_file.fmt_chunk.block_align, buffer+32, 2);
    printf("wav fmt block_align %d\n", wav_file.fmt_chunk.block_align);

    memcpy((void*)&wav_file.fmt_chunk.bits_per_sample, buffer+34, 2);
    printf("wav fmt bits_per_sample: %d\n", wav_file.fmt_chunk.bits_per_sample);

    //extension_size
    memcpy((void*)&wav_file.fmt_chunk.extension_size, buffer+36, 2);
    printf("wav fmt extension size: %s\n", wav_file.fmt_chunk.extension_size);

    memcpy((void*)&wav_file.fact_chunk.chunk_id, buffer+38, 4);
    printf("wav fact chunk id: %s\n", wav_file.fact_chunk.chunk_id);

    memcpy((void*)&wav_file.fact_chunk.chunk_size, buffer+42, 4);
    printf("wav fact chunk size: %d\n", wav_file.fact_chunk.chunk_size);

    memcpy((void*)&wav_file.fact_chunk.sample_length, buffer+46, 4);
    printf("wav fact sample_length: %d\n", wav_file.fact_chunk.sample_length);

    memcpy((void*)&wav_file.data_chunk.chunk_id, buffer+50, 4);
    printf("wav data chunk id: %s\n", wav_file.data_chunk.chunk_id);

    memcpy((void*)&wav_file.data_chunk.chunk_size, buffer+54, 4);
    printf("wav data chunk size: %d\n", wav_file.data_chunk.chunk_size);

    fclose(pFile);
    free(buffer);
    return 0;
}
