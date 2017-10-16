#include <stdio.h>
#include <stdint.h>
#include "wf_common.h"
#include "NetworkUtil.h"
#include "FileUtil.h"
#include "StringUtil.h"
#include "wf_sort.h"

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

    uint32_t  nLen = 102 << 2;
    printf("nLen = %d  ", nLen);
    msg_trace("--- new test ---");

    string xmlPath = "/opt/webex/ivr/scripts/customized/quintiles/quintiles.xml";
    string prefix = "/opt/webex/ivr/scripts/";

    string xmlFile = xmlPath.substr(prefix.length());
    msg_trace("xmlFile: "<<xmlFile);
    return 0;
}

int main(int argc, char *argv[])
{
	msg_trace("--- Walter test program ---");
	
    int nRet = 0;
    //nRet = protobuf_write(argc, argv);
	//nRet = protobuf_read(argc, argv);

    if(wfan::CNetworkUtil::IsLittleEndian()) {
		msg_trace("little endian");
	}
	else {
		msg_trace("big endian");
	}
    if(argc > 1) {
        vector<string> files;
	    nRet = RetrieveFiles(argv[1], files);
        SortUtils<string>::insert_sort(files);
        std::cout <<"--- Folder "<< argv[1] << "'s files ---"<<endl;
        for_each (files.begin(), files.end(), list_file);
        std::cout<<"--- EOF ---"<<endl;
        
	} else {

        msg_trace("--- new test ---");

        map<string, string> aMap;
        aMap["name"]= "walter";
        std::cout<<"aMap: "<< aMap.size()<<endl;

        map<string, string> bMap;
        std::cout<<"bMap: "<< bMap.size()<<endl;

        aMap.swap(bMap);
        std::cout<<"aMap: "<< aMap.size()<<endl;
        std::cout<<"bMap: "<< bMap.size()<<endl;
        
    }

	msg_trace("--- end ---");
	return nRet;
}

