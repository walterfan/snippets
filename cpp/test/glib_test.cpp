#include <string>
#include "gmock/gmock.h"
#include "glib.h"

using namespace std;
using namespace testing;

#define TEST_MAX_HEADEREXT_BYTES (16)

struct {
    guint header_count;
    guint8 header_bytes[TEST_MAX_HEADEREXT_BYTES+1];
} rtp_packet;


void fill_data(gint count, gint bytes[]) {

    rtp_packet.header_count = count;
    for (int i = 0; i < count; ++i)
    {
        rtp_packet.header_bytes[i] = bytes[i];
    }
}

TEST(glibtest, testStructure)
{
    gint data[] = {
         1, 2, 3, 4, 5, 6, 7, 8, 9,10,
        11,12,13,14,15,16,17,18,19,20,
        21,22,23,24,25
        };

    fill_data(25, data);
    g_print("\n--- rtp header extensions: %d ---\n", sizeof(rtp_packet));
    for(int i=0; i< rtp_packet.header_count; i++) {
      g_print("%d. %x, ", i, rtp_packet.header_bytes[i] & 0xff);
    }

    memset(&rtp_packet, 0, sizeof(rtp_packet));

    g_print("\n--- rtp header extensions: %d ---\n", sizeof(rtp_packet));
    for(int i=0; i < 25; i++) {
       g_print("%d. %x, ", i, rtp_packet.header_bytes[i] & 0xff);
    }

    g_print("\n");
}