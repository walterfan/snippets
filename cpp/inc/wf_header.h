/*
*
* Filename: wbxheadfile.h
* Description: head file of wmcache module
*
* Version:1.0
* Create date: 09/28/2004
* Author: walter.fan@gmail.com
*/
#ifndef __WF_HEADER_H__
#define __WF_HEADER_H__

#if !defined(_UNIX)
# define _UNIX 1
#endif

//-----------------GNU Linux header file---------------------------//
#ifdef _UNIX
	#include <unistd.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <math.h>
	#include <netdb.h>
	#include <signal.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <syslog.h>
	#include <sys/wait.h>
	#include <sys/socket.h>
	#include <sys/time.h>
	#include <sys/uio.h>
	#include <sys/stat.h>
	#include <sys/uio.h>
	#include <sys/un.h>
	#include <sys/types.h>
	#include <dirent.h>
	
	#ifdef HAVE_PTHREAD_H
	#include <pthread.h>
	#endif

	#ifdef HAVE_SYS_SELECT_H
	#include <sys/select.h>
	#endif

	#ifdef HAVE_SYS_SOCKIO_H
	#include <sys/sockio.h>
	#endif

	#ifdef HAVE_FILIO_H
	#include <sys/filio.h>
	#endif

	#ifdef HAVE_SYS_IOCTL_H
	#include <sys/ioctl.h>
	#endif

	#ifdef HAVE_TIMESPEC_STRUCT
	struct timespec
	{
		time_t tv_sec;
		long tv_nsec;
	};
	#endif
#else
	#include <windows.h>
	#include <winsock.h>
	#include <io.h>	
#endif

//-----------------Common header files ----------------------//
#include <stdint.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
//-----------------STL header files --------------------------//
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <algorithm>
//-----------------OCCI header file---------------------------//
//#include <occi.h>
//------set some data type to be compatible with Win32---------//
#ifdef _UNIX	
	typedef int boolean;
	#if !defined(int8)
	typedef char int8;
	#endif
	
	#if !defined(uint8)
	typedef unsigned char uint8;
	#endif
	
	#if !defined(int16)
	typedef short int16;
	#endif
	
	#if !defined(uint16)
	typedef unsigned short uint16;
	#endif
	
	#if !defined(int32)
	typedef long int32;
	#endif
	
	#if !defined(uint32)
	typedef unsigned long uint32;
	#endif
	
	#if !defined(float32)
	typedef float float32;
	#endif
	
	#if !defined(float64)
	typedef double float64;
	#endif
	#if !defined(TRUE)
	#define TRUE ((boolean)1)
	#endif
	
	#if !defined(FALSE)
	#define FALSE ((boolean)0)
	#endif
	
	#if !defined(NULL)
	#define NULL ((int32)0)
	#endif
	
	#define PASCAL _stdcall
	
	typedef char*			LPSTR;
	typedef const char*		LPCSTR;
	
	typedef unsigned long	DWORD;
	typedef int				BOOL;
	typedef unsigned char   BYTE;
	typedef unsigned short  WORD;
	typedef int				INT;
	typedef unsigned int	UINT;
	typedef long			LONG;
	
	typedef UINT			WPARAM;
	typedef LONG			LPARAM;
	typedef LONG			LRESULT;
	typedef int				HWND;
#else
	typedef unsigned int	u_int;	
#endif	

#endif	
