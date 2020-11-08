#ifndef _STREAM_SERVER_H
#define _STREAM_SERVER_H

#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <sys/time.h>
#include <string>
using namespace std;

namespace wfan {

typedef enum {
    wf_result_ok = 0,
    wf_result_error = 1,
    wf_result_ignore = 2,
    wf_result_not_found = 3,
    wf_result_null_ptr = 4

} wf_result_t;

class IStreamServer { 
public:
    virtual wf_result_t Initialize(map<string,string>& params);
    virtual wf_result_t Start();
    virtual wf_result_t Stop();
    virtual wf_result_t Destroy();

};

}//end of namespace

#endif