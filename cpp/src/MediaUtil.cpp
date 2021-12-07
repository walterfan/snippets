#include <iostream>
#include <arpa/inet.h>
#include "MediaUtil.h"

MediaFileParser::MediaFileParser(string& filename)
: m_filename(filename), m_filesize(0), m_nalu_count(0), m_vec_nalu(1024) {
    cout <<"MediaFileParser " << m_filename << endl;
}
MediaFileParser::~MediaFileParser() {
    cout <<"~MediaFileParser filesize=" << m_filesize << ", nal count=" << m_nalu_count << endl;
}

uint32_t MediaFileParser::parse_nalu() {
    FILE * pFile;
   
    char * buffer = NULL;
    char * nextDumpBuffer = NULL;
    size_t result;

    pFile = fopen ( m_filename.c_str() , "rb" );
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    m_filesize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*m_filesize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,m_filesize,pFile);
    if (result != m_filesize) {fputs ("Reading error",stderr); exit (3);}

    /* the whole file is now loaded in the memory buffer. */
    dump_rtp_hdr* pDumpHeader = (dump_rtp_hdr*)buffer;
    cout << "tag=" << pDumpHeader->tag  << ", len=" << pDumpHeader->len << endl;

    buffer += sizeof(dump_rtp_hdr);
    nextDumpBuffer = buffer + pDumpHeader->len;
    rtpHeader_t* pRtp = (rtpHeader_t*)buffer;

    int cc = pRtp->version & 0x0f; // cc
    
    int x = pRtp->version & 0x10;
    int m = pRtp->payloadType & 0x80;

    int minLen = 12 + 4 * cc;
    if(x) {
        uint16_t* pWord = (uint16_t*)(buffer + minLen);
        minLen += 4;

        int extProfile = ntohs(*pWord);
        uint32_t extSize = ntohs(*(pWord + 1))*4;
        minLen += extSize;
        
    }
    cout << "pt=" << (pRtp->payloadType & 0x7f) <<
    ", sn=" << ntohs(pRtp->seqNo) <<
    ", ts=" << ntohl(pRtp->timestamp)  <<
    ", ssrc=" <<ntohl(pRtp->mediaSSRC) <<
    ", cc=" << cc <<
    ", x=" << x <<
    ", m=" << m << endl;

    buffer += minLen;
    // NAL Unit Header
    uint8_t *pNalHeader = (uint8_t*)buffer;
    int naluType = *pNalHeader & 0x1f;
    cout << "naluType=" << naluType << endl;
    //5: IDR, 6: SEI, 7: SPS, 8: PPS
    //24: STAP-A
    if(naluType == 24) {

    }
    // NAL Unit
    
    //free (buffer);
    fclose (pFile);
    return 0;
}

int MediaFileParser::find_nal_unit(uint8_t* buf, int size, int* nal_start, int* nal_end) {
    return 0;
}