/*
 * CNetworkUtil.h
 *
 *  Created on: 2013-8-6
 *      Author: walter_2
 */

#ifndef CNETWORKUTIL_H_
#define CNETWORKUTIL_H_
#include <netdb.h>
#include <string>

namespace wfan {

typedef int SOCKET;
/* External variables */
extern int h_errno;    /* defined by BIND for DNS errors */
extern char **environ; /* defined by libc */

/* Misc constants */
#define MAXLINE  8192  /* max text line length */
#define MAXBUF   8192  /* max I/O buffer size */
#define LISTENQ  1024  /* second argument to listen() */

class CNetworkUtil {
public:
    static int CreateSocket(int type, int protocol);
    static void CloseSocket(int nSocket);

    static int Connect(char *szHostname, int nPort);
    static int Listen(int nPort);

    static bool IsLittleEndian();
    static void SwapByteOrder(void* pData, int nSize);

    static struct hostent * GetHostName(const char* szAddr);
    static void ResolveAddress(const char* szHost);
    static void PrintAddress(struct hostent*pHost);
    static int FillAddress(const string strAddr, unsigned short port, sockaddr_in& sAddr);

    static void SetAddress(const char* szHostName, const char* szServName, struct sockaddr_in* pSAddr,const char* szProtocol);
    static int TcpServer(const char* szHost, const char* szPort);
    static int TcpClient(const char* szHost, const char* szPort);

    static int UdpServer(const char* szHost, const char* szPort);
    static int UdpClient(const char* szHost, const char* szPort, struct sockaddr_in *sap);

private:
    CNetworkUtil();
    CNetworkUtil(CNetworkUtil& aUtil);
    ~CNetworkUtil();
};

} /* namespace wfan */
#endif /* CNETWORKUTIL_H_ */
