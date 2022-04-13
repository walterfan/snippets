#include <stdio.h>
#include <stdint.h>
#include "wf_common.h"
#include "NetworkUtil.h"
#include "FileUtil.h"
#include "StringUtil.h"
#include "wf_sort.h"
#include "MediaUtil.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>

using namespace std;
using namespace wfan;

typedef uint16_t sequence_number_t;   /* 16 bit sequence number  */
typedef uint32_t rollover_counter_t;   /* 32 bit rollover counter */

#define seq_num_median (1 << (8*sizeof(sequence_number_t) - 1))
#define seq_num_max    (1 << (8*sizeof(sequence_number_t)))

extern int show_bytes_test(int argc, char *argv[]);
extern int protobuf_read(int argc, char *argv[]);
extern int protobuf_write(int argc, char *argv[]);
extern int rtp_util_test(int argc, char *argv[]);
extern void show_bytes(uint8_t* start, int len);

void list_file (string i) {  // function:
  std::cout << i  << endl;
}

struct FileLister {           // function object type:
  void operator() (string i) {std::cout << i << endl;}
} myobject;

int test(int argc, char *argv[])
{
    msg_trace("--- embed quick test ---");
    uint16_t num = 0x1234;
    printf("local order    %d (0x1234): ", num);
    show_bytes((uint8_t*)&num, 2);
    uint16_t esn = htons(num);
    printf("big endia(net) %d (0x1234): ", num);
    show_bytes((uint8_t*)&esn, 2);
    uint8_t byte1 = esn>>8;
    uint8_t byte2 = esn & 0xff;
    show_bytes(&byte1, 1);
    show_bytes(&byte2, 1);

    int nTag = 0xBEDE;
    show_bytes((uint8_t*)&nTag, 4);

    if(wfan::CNetworkUtil::IsLittleEndian()) {
      msg_trace("little endian");
    }
    else {
      msg_trace("big endian");
    }

    vector<string> files;
    int nRet = RetrieveFiles(argv[1], files);
    SortUtils<string>::insert_sort(files);
    std::cout <<"--- Folder "<< argv[1] << "'s files ---"<<endl;
    for_each (files.begin(), files.end(), list_file);
    std::cout<<"--- EOF ---"<<endl;

    return nRet;
}


enum COLOR {
  RED,
  GREEN,
  BLUE,
  BLACK,
  WHITE
};

inline std::ostream& operator<<(std::ostream& o, COLOR color) {
    switch (color) {
        case RED:
            o << "red";
            break;
        case GREEN:
            o << "green";
            break;
        default:
            o << "unknown";
    }
    return o;
}

const std::map<COLOR, std::string> MAP_OF_COLOR = {
    {RED, "red"},
    {GREEN, "green"},
    {BLUE, "blue"},
    {BLACK, "black"},
    {WHITE, "white"}};

void quick_test() {

    std::for_each(MAP_OF_COLOR.begin(), MAP_OF_COLOR.end(),
                  [](std::pair<COLOR, std::string> pair) {
                      std::ostringstream oss;
                      COLOR color = pair.first;
                      std::string& color_name = pair.second;
                      oss << color;
                      std::cout << oss.str() << "--" << color_name << std::endl;
                      
                  });
}

int main(int argc, char *argv[])
{
	msg_trace("--- Walter test program ---");
	
  int nRet = 0;  
  if(argc > 1) {
     msg_trace("--- read media file ---");
     string media_file = argv[1];
     MediaFileParser* pParser = new MediaFileParser(media_file);
     pParser->parse_stream();
     delete pParser;
     msg_trace("--- byebye ---");
	} else {
     quick_test();
     msg_trace("Usage: " << argv[0] << " <media_file>");
  }
	return nRet;
}

