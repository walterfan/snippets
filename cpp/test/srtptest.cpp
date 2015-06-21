#include "gmock/gmock.h"
#include <string>
#include <iostream>
#include "srtp.h"
#include "srtp_priv.h"

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

#define MTU 2048
#define MAX_PRINT_STRING_LEN 1024

char packet_string[MTU];

class CSRTPUtil
{
private:
    CSRTPUtil();
    ~CSRTPUtil();
};

unsigned char test_key[30] = {
    0xe1, 0xf9, 0x7a, 0x0d, 0x3e, 0x01, 0x8b, 0xe0,
    0xd6, 0x4f, 0xa3, 0x2c, 0x06, 0xde, 0x41, 0x39,
    0x0e, 0xc6, 0x75, 0xad, 0x49, 0x8a, 0xfe, 0xeb,
    0xb6, 0x96, 0x0b, 0x3a, 0xab, 0xe6
};

extern char * octet_string_hex_string(const void *s, int length);

char * srtp_packet_to_string(srtp_hdr_t *hdr, int pkt_octet_len) {
  int octets_in_rtp_header = 12;
  uint8_t *data = ((uint8_t *)hdr)+octets_in_rtp_header;
  int hex_len = pkt_octet_len-octets_in_rtp_header;

  /* sanity checking */
  if ((hdr == NULL) || (pkt_octet_len > MTU))
    return NULL;

  /* write packet into string */
  sprintf(packet_string,
      "(s)rtp packet: {\n"
      "   version:\t%d\n"
      "   p:\t\t%d\n"
      "   x:\t\t%d\n"
      "   cc:\t\t%d\n"
      "   m:\t\t%d\n"
      "   pt:\t\t%x\n"
      "   seq:\t\t%x\n"
      "   ts:\t\t%x\n"
      "   ssrc:\t%x\n"
      "   data:\t%s\n"
      "} (%d octets in total)\n",
      hdr->version,
      hdr->p,
      hdr->x,
      hdr->cc,
      hdr->m,
      hdr->pt,
      hdr->seq,
      hdr->ts,
      hdr->ssrc,
      octet_string_hex_string(data, hex_len),
      pkt_octet_len);

  return packet_string;
}

srtp_hdr_t *
srtp_create_test_packet(int pkt_octet_len, uint32_t ssrc) {
  int i;
  uint8_t *buffer;
  srtp_hdr_t *hdr;
  int bytes_in_hdr = 12;

  /* allocate memory for test packet */
  hdr = (srtp_hdr_t*)malloc(pkt_octet_len + bytes_in_hdr
           + SRTP_MAX_TRAILER_LEN + 4);
  if (!hdr)
    return NULL;

  hdr->version = 2;              /* RTP version two     */
  hdr->p    = 0;                 /* no padding needed   */
  hdr->x    = 0;                 /* no header extension */
  hdr->cc   = 0;                 /* no CSRCs            */
  hdr->m    = 0;                 /* marker bit          */
  hdr->pt   = 0xf;               /* payload type        */
  hdr->seq  = htons(0x1234);     /* sequence number     */
  hdr->ts   = htonl(0xdecafbad); /* timestamp           */
  hdr->ssrc = htonl(ssrc);       /* synch. source       */

  buffer = (uint8_t *)hdr;
  buffer += bytes_in_hdr;

  /* set RTP data to 0xab */
  for (i=0; i < pkt_octet_len; i++)
    *buffer++ = 0xab;

  /* set post-data value to 0xffff to enable overrun checking */
  for (i=0; i < SRTP_MAX_TRAILER_LEN+4; i++)
    *buffer++ = 0xff;

  return hdr;
}

TEST(SRTPTest, protect)
 {
    cout<<"--- SRTPTest.protect --"<<endl;

    int msg_len_octets = 80;
    srtp_policy_t policy;

    srtp_t aSrtpSession;
    srtp_hdr_t *pSrtpMsg;
    int i;
    clock_t timer;
    int num_trials = 2;
    int len;
    uint32_t ssrc;
    err_status_t status;

    status = srtp_init();
    EXPECT_TRUE(status==err_status_ok);

    crypto_policy_set_rtp_default(&policy.rtp);
    crypto_policy_set_rtcp_default(&policy.rtcp);
    policy.ssrc.type  = ssrc_specific;
    policy.ssrc.value = 0xdecafbad;
    policy.key  = test_key;
    policy.next = NULL;
    /*
     * allocate and initialize an srtp session
     */
    status = srtp_create(&aSrtpSession, &policy);
    if (status) {
        printf("error: srtp_create() failed with error code %d\n", status);
        exit(1);
    }
    EXPECT_TRUE(status == err_status_ok);

    /*
     * if the ssrc is unspecified, use a predetermined one
     */
    if (policy.ssrc.type != ssrc_specific) {
        ssrc = 0xdeadbeef;
    } else {
        ssrc = policy.ssrc.value;
    }

    /*
     * create a test packet
     */
    pSrtpMsg = srtp_create_test_packet(msg_len_octets, ssrc);
    ASSERT_TRUE(pSrtpMsg != NULL);

    cout<<"srtp packet (unprotected): "<<srtp_packet_to_string(pSrtpMsg, msg_len_octets)<<endl;

    timer = clock();
    for (i = 0; i < num_trials; i++) {
        err_status_t status;
        len = msg_len_octets + 12; /* add in rtp header length */

        /* srtp protect message */
        status = srtp_protect(aSrtpSession, pSrtpMsg, &len);
        if (status) {
            printf("error: srtp_protect() failed with error code %d\n", status);
            exit(1);
        }
        cout<<"srtp packet (protected): "<<srtp_packet_to_string(pSrtpMsg, len)<<endl;
        /* increment message number */
        pSrtpMsg->seq = htons(ntohs(pSrtpMsg->seq) + 1);

    }
    timer = clock() - timer;

    free(pSrtpMsg);

}
/*
TEST(SRTPTest, encryption)
{
    cout<<"--- SRTPTest.encryption --"<<endl;

    srtp_t session;
    srtp_policy_t policy;

    err_status_t status = srtp_init();
    ASSERT_TRUE(err_status_ok == status);

    //status = crypto_kernel_load_debug_module(&mod_driver);
    //ASSERT_TRUE(err_status_ok == status);

    crypto_policy_set_rtp_default(&policy.rtp);
    crypto_policy_set_rtcp_default(&policy.rtcp);
    policy.ssrc.type  = ssrc_specific;
    policy.ssrc.value = 0xdecafbad;
    policy.key  = test_key;
    policy.next = NULL;

    srtp_create(&session, &policy);
    char rtp_buffer[2048];
    unsigned nLen = 0;
}
*/
