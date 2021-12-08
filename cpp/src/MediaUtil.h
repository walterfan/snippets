#ifndef __MEDIA_UTIL_H__
#define __MEDIA_UTIL_H__

#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

typedef struct rtpHeader {
    uint8_t  version;
    uint8_t  payloadType;
    uint16_t seqNo;
    uint32_t timestamp;
    uint32_t mediaSSRC;
    uint8_t  payload[1];
} rtpHeader_t;


typedef struct {
    char tag[4];
    uint32_t len;
} dump_rtp_hdr;


struct NALU {

    enum Type {
        kUnspecified = 0,
        kNonIDRSlice = 1,
        kSliceDataA = 2,
        kSliceDataB = 3,
        kSliceDataC = 4,
        kIDRSlice = 5,
        kSEIMessage = 6,
        kSPS = 7,
        kPPS = 8,
        kAUD = 9,
        kEOSeq = 10,
        kEOStream = 11,
        kFiller = 12,
        kSPSExt = 13,
        kReserved14 = 14,
        kReserved15 = 15,
        kReserved16 = 16,
        kReserved17 = 17,
        kReserved18 = 18,
        kCodedSliceAux = 19,
        kCodedSliceExtension = 20,
  };

    uint8_t* buf;
    uint32_t len;
    int nal_ref_idc;
    int nal_unit_type;
};


class MediaFileParser {
public:
    MediaFileParser(string& filename);
    ~MediaFileParser();

    MediaFileParser() = delete;
    MediaFileParser(const MediaFileParser&) = delete;
    MediaFileParser& operator=(const MediaFileParser&) = delete;


    int parse_stream();
    int handle_packet(uint8_t* pPacket, int len);
    int handle_nalu(uint8_t* pPacket, int len);
    
    int handle_stap(uint8_t* pPacket, int len);
    int handle_fu(uint8_t* pPacket, int len);



private:
    string m_filename;
    size_t m_filesize;
    size_t m_nalu_count;
    vector<NALU> m_vec_nalu;
};



#endif