/*
* Copyright  2005 JinWei Bird Studio All rights reserved
*
* Filename: wf_base.h
* Description: base header file
*
* Version:1.0
* Create date: 08/19/2005
* Author: Walter Fan, walter.fan@gmail.com
*/

#include "wf_header.h"
#ifndef __WF_BASE_H__
#define __WF_BASE_H__

using namespace std;

extern char* get_cur_info(char* szBuf, int len);

#ifdef _UNIX
		#define SEPARATOR '/'
#else
		#define SEPARATOR '\\'
#endif

#define msg_log(file,msg) msg2log(file,msg,__FILE__,__LINE__)

#define WF_ASSERT(condition,msg) {	\
		if(!(condition)){							\
			cout<<" Assertion failed:"<<__FILE__<<","<<__LINE__<<": "<<msg<<endl;\
			exit(EXIT_FAILURE);							\
		}							\
}

#ifndef __error_t_defined
	typedef int error_t;
	#define __error_t_defined
#endif

#define VAR_TRACE(out, var) {\
	char _theLogBuf[256];\
	out<<get_cur_info(_theLogBuf, 256)<<" ("<<__FILE__<<","<<__LINE__<<")\t"<<#var<<"="<<var<<std::endl;\
}

#define MSG_TRACE(out, msg) {\
	char _theLogBuf[256];\
	out<<get_cur_info(_theLogBuf, 256)<<" ("<<__FILE__<<","<<__LINE__<<")\t"<<msg<<std::endl;\
}

#define err_trace(msg) MSG_TRACE(std::cerr, msg)
#define msg_trace(msg) MSG_TRACE(std::cout, msg)
#define var_trace(msg) VAR_TRACE(std::cout, msg)

#define ERR_RETURN(ret,fmt, ...) \
    do { \
        if (!ret) {\
            fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); \
            return ret;\
        }\
    } while (0)


#ifndef FALSE
    #define FALSE 0
#endif // FALSE

#ifndef TRUE
    #define TRUE 1
#endif // TRUE

#define DEFAULT_BACK_LOG 1024


#ifndef CERR
#define CERR std::cerr <<"\n["<<time(NULL)<<"]\t"<< __FILE__ << "," << std::dec << __LINE__ << " : "
#endif

#ifndef COUT
#define COUT std::cout <<"\n["<<time(NULL)<<"]\t"<< __FILE__ << "," << std::dec << __LINE__ << " : "
#endif

#ifndef ASSERT
#define ASSERT(condition) { \
    if(!(condition)) \
    { \
        std::cerr << "ASSERT FAILED: " << #condition << " @ "; \
        std::cerr << __FILE__ << " (" << __LINE__ << ")" << std::endl; \
    }}
#endif

#ifndef ASSERT_RET
#define ASSERT_RET(condition, retval) { \
    if(!(condition)) \
    { \
        std::cerr << "ASSERT FAILED: " << #condition << " @ "; \
        std::cerr << __FILE__ << " (" << __LINE__ << ")" << std::endl; \
        return retval;\
    }}
#endif

#ifndef ASSERT_RET_VOID
#define ASSERT_RET_VOID(condition) { \
    if(!(condition)) \
    { \
        std::cerr << "ASSERT FAILED: " << #condition << " @ "; \
        std::cerr << __FILE__ << " (" << __LINE__ << ")" << std::endl; \
        return;\
    }}
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) \
    do \
    { \
        if(NULL != p) \
        { \
            delete p; \
            p = NULL; \
        } \
    } while(0)
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) \
    do \
    { \
        if(NULL != p) \
        {\
            delete [] p; \
            p = NULL; \
        } \
    } while(0)
#endif

#ifndef SAFE_ADDREF
#define SAFE_ADDREF(p) if(p)\
    {\
        p->AddReference();\
    }

#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) \
    do \
    { \
        if(NULL != p) \
        { \
            p->ReleaseReference(); \
            p = NULL; \
        } \
    } while(0)
#endif

//put it in private section to disallow evil copy constructor and operator=
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);  \
    TypeName& operator=(const TypeName&)
#endif

//put it in private section to disallow implicit and copy constructor and operator=
#ifndef DISALLOW_IMPLICIT_CONSTRUCTORS
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
    TypeName(); \
    DISALLOW_COPY_AND_ASSIGN(TypeName)
#endif

#endif
