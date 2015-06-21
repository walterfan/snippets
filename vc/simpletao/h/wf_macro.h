/*---------------------------------------------------------------
    File: 
        Macros.h
  
    Description:
        macro utilities

    Author:
        Walter Fan    (walterfan@qq.com)                
                                                      
    History:
        1/25/2010  Create                                

----------------------------------------------------------------*/ 
#include <iostream>

#ifndef __WF_MACRO_UTIL__
#define __WF_MACRO_UTIL__

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

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) \
    do \
    { \
        if(NULL != p) \
        { \
            p->release_reference(); \
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

#define DISALLOW_EVIL_CONSTRUCTORS(TypeName) \
    TypeName(const TypeName&);  \
    TypeName& operator=(const TypeName&)

#define msg_trace(msg)	std::cout<<__FILE__<<","<<__LINE__<<": " << msg <<std::endl

#define err_trace(msg)	std::cout<<"[ERROR] "<<__FILE__<<","<<__LINE__<<": " << msg <<std::endl

#define msg_printf(fmt,...) printf("%s, %d: "fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#ifdef DEBUG
	#define debug_printf printf("%s, %d"fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
	#define debug_printf
#endif

#define PRINT_HEX(x) printf("%s = %#10x \n", #x, x)

#endif // end of __WF_MACRO_UTIL__
