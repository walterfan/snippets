#ifndef __WF_TYPES_H__
#define __WF_TYPES_H__

#include "wf_define.h"

/** Time relative to server start. Smaller than time_t on 64-bit systems. */
typedef unsigned int rel_time_t;

// ============================================================
//  This defines windows datatype
// ============================================================

typedef U1 BYTE;
typedef U2 WORD;
typedef U4 DWORD;

typedef void * LPVOID;
typedef void ** LPPVOID;
typedef const char * LPCSTR;
typedef char *       LPSTR;
typedef char **      LPPSTR;

typedef BYTE *       LPBYTE;
typedef BYTE **      LPPBYTE;

#ifndef INFINITE
    #define INFINITE (DWORD)-1
#endif //INFINITE


// ============================================================
//  This defines the 64 bit datatype
// ============================================================

// ------------------------------
//  LINUX
// ------------------------------
#ifdef __GNUC__
	typedef long long int int64;
    typedef long long int sint64;
    typedef unsigned long long int uint64;
#endif


// ------------------------------
//  Visual C++
// ------------------------------
#ifdef WIN32
	typedef __int64 int64;
    typedef __int64 sint64;
    typedef unsigned __int64 uint64;
#endif

const double pi = 3.1415926535897932384626433832795;

// ------------- common types -------------------
  typedef int CmResult;

  typedef int CM_HANDLE;
  typedef CM_HANDLE CM_SOCKET;

#ifndef WIN32
  typedef long long           LONGLONG;
  typedef unsigned int       DWORD;
  typedef long                LONG;
  typedef unsigned long       ULONG;
  typedef int                 BOOL;
  typedef unsigned char       BYTE;
  typedef unsigned short        WORD;
  typedef float                 FLOAT;
  typedef int                   INT;
  typedef unsigned int          UINT;
  typedef FLOAT                *PFLOAT;
  typedef BOOL                 *LPBOOL;
  typedef int                  *LPINT;
  typedef WORD                 *LPWORD;
  typedef long                 *LPLONG;
  typedef DWORD                *LPDWORD;
  typedef unsigned int         *LPUINT;
  typedef void                 *LPVOID;
  typedef const void           *LPCVOID;
  typedef char                  CHAR;
  typedef char                  TCHAR;
  typedef unsigned short        WCHAR;
  typedef const char           *LPCSTR;
  typedef char                 *LPSTR;
  typedef const unsigned short *LPCWSTR;
  typedef unsigned short       *LPWSTR;
  typedef BYTE                 *LPBYTE;
  typedef const BYTE           *LPCBYTE;

  typedef uint64_t UINT64;
  typedef uint32_t UINT32;
  typedef uint16_t UINT16;
  typedef uint8_t  UINT8;

  typedef int64_t  INT64;
  typedef int32_t  INT32;
  typedef int16_t  INT16;
  typedef int8_t   INT8;

  typedef long long int _int64;
  typedef _int64        __int64;
#endif
#endif
