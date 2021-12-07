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

    /**
     * Parse FU (fragment NAL). For SVC in WebEx format, it can contain different nalTypes.
     * @fp         -- the file handler
     * @return     -- the NALU count
     */
    uint32_t parse_nalu();

private:


    int find_nal_unit(uint8_t* buf, int size, int* nal_start, int* nal_end);

    string m_filename;
    size_t m_filesize;
    size_t m_nalu_count;
    vector<NALU> m_vec_nalu;
};



#endif