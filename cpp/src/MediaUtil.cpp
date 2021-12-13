#include <iostream>
#include <arpa/inet.h>
#include "MediaUtil.h"


#define debug_trace(msg)  do { if(0) {	std::cout<<__FILE__<<","<<__LINE__<<": " << msg <<std::endl; } } while(0)

#define msg_trace(msg)	std::cout<<__FILE__<<","<<__LINE__<<": " << msg <<std::endl

#define err_trace(msg)	std::cout<<"[ERROR] "<<__FILE__<<","<<__LINE__<<": " << msg <<std::endl

MediaFileParser::MediaFileParser(string& filename)
: m_filename(filename), m_filesize(0), m_nalu_count(0), m_input_file(NULL), m_output_file(NULL), m_vec_nalu(1024) {
    m_h264_file = filename + ".h264";
    cout <<"MediaFileParser " << m_filename << " to " << m_h264_file << endl;
}
MediaFileParser::~MediaFileParser() {
    cout <<"~MediaFileParser filesize=" << m_filesize << ", nal count=" << m_nalu_count << endl;
}

int MediaFileParser::parse_stream() {
 
    size_t result = 0;

    m_input_file = fopen ( m_filename.c_str() , "rb" );
    m_output_file = fopen ( m_h264_file.c_str() , "wb" );

    if (m_input_file==NULL) {
        fputs ("File error",stderr); exit (1);
    }

    // obtain file size:
    fseek (m_input_file , 0 , SEEK_END);
    m_filesize = ftell (m_input_file);
    rewind (m_input_file);

    //sizeof(dump_rtp_hdr)=8
    char pktBuf[2048];
    cout << "# ,";
    RtpInfo::printTitles(cout);
    int i = 0;
    while(!feof(m_input_file)) {
        result = fread (pktBuf, 1, 8, m_input_file);
        if(result < 8) {
            err_trace("dump header only read" << result);
            break;
        }

        dump_rtp_hdr* pDumpHeader = (dump_rtp_hdr*)pktBuf;
        debug_trace("tag=" << pDumpHeader->tag[0] << pDumpHeader->tag[1] 
          << pDumpHeader->tag[2] << pDumpHeader->tag[3] 
          << ", len=" << pDumpHeader->len);
        int pktLen = pDumpHeader->len;

        result = fread(pktBuf, 1, pktLen, m_input_file);
        if(result < pktLen) {
            err_trace("packet only read " << result << ", should be " << pktLen);
            break;
        }
        rtp_info_t rtpInfo;
        this->handle_packet((uint8_t*)pktBuf, pktLen, rtpInfo);
        cout << (++i) << ", ";
        rtpInfo.printValues(cout);
        //cout << rtpInfo <<endl;

    }

    fclose(m_input_file);
    fclose(m_output_file);

    return 0;
}


int MediaFileParser::handle_packet(uint8_t* pPacket, int len, rtp_info_t& rtpInfo) {
    rtpHeader_t* pRtp = (rtpHeader_t*)pPacket;

    int cc = pRtp->version & 0x0f; // cc
    
    int x = pRtp->version & 0x10;
    int m = pRtp->payloadType & 0x80;

    int minLen = 12 + 4 * cc;
    if(x) {
        uint16_t* pWord = (uint16_t*)(pPacket + minLen);
        minLen += 4;

        //int extProfile = ntohs(*pWord);
        uint32_t extSize = ntohs(*(pWord + 1))*4;
        minLen += extSize;
        
    }

    if(cc) {
        //TODO: + size of csrc
    }

    rtpInfo.put("pt",  to_string(pRtp->payloadType & 0x7f));
    rtpInfo.put("size" ,  to_string(len));
    rtpInfo.put("sn" ,  to_string(ntohs(pRtp->seqNo) ));
    rtpInfo.put("ts" ,  to_string(ntohl(pRtp->timestamp) ));
    rtpInfo.put("ssrc" ,  to_string(ntohl(pRtp->mediaSSRC) ));
    rtpInfo.put("cc" ,  to_string( cc ));
    rtpInfo.put("x" ,  to_string( x ));
    rtpInfo.put("m" ,  to_string( m ));

    if( len <= minLen) return -1;

    pPacket += minLen;
    return handle_nalu(pPacket, len - minLen, rtpInfo);
}

int MediaFileParser::handle_nalu(uint8_t* pPacket, int len, rtp_info_t& rtpInfo) {
    char p8[4] = {0,0,0,1};
    fwrite(p8, 1, 4, m_output_file);
    fwrite(pPacket, 1, len, m_output_file);

    // NAL Unit Header
    uint8_t *pNalHeader = (uint8_t*)pPacket;
    int naluType = *pNalHeader & 0x1f;
    rtpInfo.put("nalType", to_string(naluType));
    //5: IDR, 6: SEI, 7: SPS, 8: PPS
    //24: STAP-A, 28: FU-A
    if (naluType == 24) {
        handle_stap(pPacket, len, rtpInfo);
    } else if(naluType == 28) {
        handle_fu(pPacket, len, rtpInfo);
    } 
    // parse NAL Unit
    m_nalu_count++;
    return 0;
}

int MediaFileParser::handle_stap(uint8_t* pPacket, int len, rtp_info_t& rtpInfo) {
    pPacket ++;
    //nalu_size: 2 bytes
    int leftPayloadSize = len;
    while (leftPayloadSize > 3) {
        int nalSize = ((*pPacket << 8) & 0x0ff00) + (*(pPacket+1) & 0x0ff);
        int subNalType = (*(pPacket+2) & 0x01f);
        rtpInfo.put("subNalType", to_string(subNalType));
        pPacket += (2 + nalSize);
        leftPayloadSize -= (2 + nalSize);
    }
    return 0;
}

/*
FU header:
      +---------------+
      |0|1|2|3|4|5|6|7|
      +-+-+-+-+-+-+-+-+
      |S|E|R|  Type   |
      +---------------+
*/

int MediaFileParser::handle_fu(uint8_t* pPacket, int len, rtp_info_t& rtpInfo) {
    pPacket ++;
    bool bStart = false, bEnd = false;
    int subNalType = (*pPacket)&0x1f;
    if ((*pPacket) & 0x40) { bEnd = true; }   
    if ((*pPacket) & 0x80) { bStart = true; } 
    rtpInfo.put("subNalType", to_string(subNalType));
    rtpInfo.put("start", to_string(bStart));
    rtpInfo.put("end", to_string(bEnd));
    return 0;
}
