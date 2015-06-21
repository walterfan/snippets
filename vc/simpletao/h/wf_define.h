/*------------------------------------------------------*/
/* Define Gloabal Variables                             */
/*                                                      */
/* Defines.h                                            */
/*                                                      */
/*                                                      */
/* Author:                                              */
/*    Walter Fan Ya Min  walter.fan@gmail.com           */
/*                                                      */
/* History:                                             */
/*    2/26/2010   Create                                */
/*                                                      */
/*------------------------------------------------------*/
#ifndef __WF_DEFINES__
#define __WF_DEFINES__

#ifdef WIN32
  #ifndef WF_WIN32
    #define WF_WIN32
  #endif // WF_WIN32
#endif // WIN32

#ifdef UNIX
  #ifndef WF_UNIX
    #define WF_UNIX
  #endif // WF_UNIX
#endif // UNIX

#ifdef LINUX
  #ifndef WF_LINUX
    #define WF_LINUX
  #endif // WF_LINUX
  #ifndef WF_UNIX
    #define WF_UNIX
  #endif // WF_UNIX
#endif // LINUX
	
#ifdef WF_WIN32
	#ifdef _LIB
		#define WF_EXPORT
	#else
		#ifdef _USRDLL
			#define WF_EXPORT __declspec(dllexport)
		#else
			#define WF_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define WF_EXPORT
#endif

typedef long WfResult;

#ifdef WF_WIN32
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif // NOMINMAX

  // supports Windows NT 4.0 and later, not support Windows 95.
  // mainly for using winsock2 functions
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0400
   #endif // _WIN32_WINNT
  //#include <windows.h>
  #include <winsock2.h>

  // The ordering of the fields in this struct is important. 
  // It has to match those in WSABUF.
  struct iovec
  {
    u_long iov_len; // byte count to read/write
    char *iov_base; // data to be read/written
  };

  #define EWOULDBLOCK             WSAEWOULDBLOCK
  #define EINPROGRESS             WSAEINPROGRESS
  #define EALREADY                WSAEALREADY
  #define ENOTSOCK                WSAENOTSOCK
  #define EDESTADDRREQ            WSAEDESTADDRREQ
  #define EMSGSIZE                WSAEMSGSIZE
  #define EPROTOTYPE              WSAEPROTOTYPE
  #define ENOPROTOOPT             WSAENOPROTOOPT
  #define EPROTONOSUPPORT         WSAEPROTONOSUPPORT
  #define ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
  #define EOPNOTSUPP              WSAEOPNOTSUPP
  #define EPFNOSUPPORT            WSAEPFNOSUPPORT
  #define EAFNOSUPPORT            WSAEAFNOSUPPORT
  #define EADDRINUSE              WSAEADDRINUSE
  #define EADDRNOTAVAIL           WSAEADDRNOTAVAIL
  #define ENETDOWN                WSAENETDOWN
  #define ENETUNREACH             WSAENETUNREACH
  #define ENETRESET               WSAENETRESET
  #define ECONNABORTED            WSAECONNABORTED
  #define ECONNRESET              WSAECONNRESET
  #define ENOBUFS                 WSAENOBUFS
  #define EISCONN                 WSAEISCONN
  #define ENOTCONN                WSAENOTCONN
  #define ESHUTDOWN               WSAESHUTDOWN
  #define ETOOMANYREFS            WSAETOOMANYREFS
  #define ETIMEDOUT               WSAETIMEDOUT
  #define ECONNREFUSED            WSAECONNREFUSED
  #define ELOOP                   WSAELOOP
  #define EHOSTDOWN               WSAEHOSTDOWN
  #define EHOSTUNREACH            WSAEHOSTUNREACH
  #define EPROCLIM                WSAEPROCLIM
  #define EUSERS                  WSAEUSERS
  #define EDQUOT                  WSAEDQUOT
  #define ESTALE                  WSAESTALE
  #define EREMOTE                 WSAEREMOTE
#endif // WF_WIN32

#ifdef WF_WIN32
  typedef HANDLE WF_HANDLE;
  typedef SOCKET WF_SOCKET;
  #define WF_INVALID_HANDLE INVALID_HANDLE_VALUE
  #define WF_SD_RECEIVE SD_RECEIVE
  #define WF_SD_SEND SD_SEND
  #define WF_SD_BOTH SD_BOTH
#else // !WF_WIN32
  typedef int WF_HANDLE;
  typedef WF_HANDLE WF_SOCKET;
  #define WF_INVALID_HANDLE -1
  #define WF_SD_RECEIVE 0
  #define WF_SD_SEND 1
  #define WF_SD_BOTH 2
#endif // WF_WIN32

#ifndef WF_WIN32
  typedef long long           LONGLONG;
  typedef unsigned long       DWORD;
  typedef long                LONG;
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
  
  #ifndef FALSE
    #define FALSE 0
  #endif // FALSE
  #ifndef TRUE
    #define TRUE 1
  #endif // TRUE
#endif // !WF_WIN32


#if defined(WIN32)
	#define S1	signed char
	#define S2	signed short
	#define S4	signed long
	#define S8	signed __int64	

	#define U1	unsigned char
	#define U2	unsigned short
	#define U4	unsigned long
	#define U8	unsigned __int64

/*
	Use ANSI-754 standard for single and double precision floats
	single precision = 4 bytes
	double precision = 8 bytes
*/

	#define F4	float
	#define F8	double
#else
	#define S1	signed char
	#define S2	signed short
	#define S4	signed long
	#define S8	signed long long	

	#define U1	unsigned char
	#define U2	unsigned short
	#define U4	unsigned long
	#define U8	unsigned long long

	/*
		Use ANSI-754 standard for single and double precision floats
		single precision = 4 bytes
		double precision = 8 bytes
	*/

	#define F4	float
	#define F8	double
#endif

#ifndef FALSE
    #define FALSE 0
#endif // FALSE
#ifndef TRUE
    #define TRUE 1
#endif // TRUE


#if HAVE_STDINT_H
	# include <stdint.h>
#else
 typedef unsigned char             uint8_t;
#endif

/* unistd.h is here */
#if HAVE_UNISTD_H
# include <unistd.h>
#endif

#ifndef RET_FAILED
    #define RET_FAILED -1
#endif 

#ifndef RET_SUCCESS
    #define RET_SUCCESS 1
#endif 

#ifdef WF_WIN32
	typedef DWORD WF_THREAD_ID;
	typedef HANDLE WF_THREAD_HANDLE;
#else
	typedef pthread_t WF_THREAD_ID;
	typedef pthread_t WF_THREAD_HANDLE;
#endif

#endif //__WF_DEFINES__
