#include <iostream>
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
   
    char * buffer;
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

    // terminate
    fclose (pFile);
    free (buffer);
    return 0;
}

int MediaFileParser::find_nal_unit(uint8_t* buf, int size, int* nal_start, int* nal_end) {
    return 0;
}