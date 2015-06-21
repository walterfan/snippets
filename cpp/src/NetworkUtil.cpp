/*
 * CNetworkUtil.cpp
 *
 *  Created on: 2013-8-6
 *      Author: walter_2
 */
#include "wf_common.h"
#include "NetworkUtil.h"

namespace wfan {

#ifdef WIN32
static bool s_bInitialized = false;
#endif

#define set_errno(e)	errno = ( e )
#define isvalidsock(s)	( ( s ) >= 0 )
#define NLISTEN 50

typedef struct sockaddr SA;

int CNetworkUtil::FillAddress(const string strAddr, unsigned short port, sockaddr_in& sAddr)
{
    memset(&sAddr, 0, sizeof(sAddr));
    sAddr.sin_family = AF_INET;

    hostent *pHost;
    if ((pHost = gethostbyname(strAddr.c_str())) == NULL) {
        err_trace("Failed to resolve name (gethostbyname())");
        return -1;
    }
    //bcopy((char *)hp->h_addr_list[0],(char *)&serveraddr.sin_addr.s_addr, hp->h_length);
    sAddr.sin_addr.s_addr = *((unsigned long *) pHost->h_addr_list[0]);
    sAddr.sin_port = htons(port);
    return 0;
}


int CNetworkUtil::CreateSocket(int type, int protocol)
{
    #ifdef WIN32
    if (!s_bInitialized) {
        WORD wVersionRequested;
        WSADATA wsaData;

        wVersionRequested = MAKEWORD(2, 0);              // Request WinSock v2.0
        if (WSAStartup(wVersionRequested, &wsaData) != 0) {  // Load WinSock DLL
        error_trace("Unable to load WinSock DLL");
        }
        s_bInitialized = true;
    }
    #endif

    return socket(PF_INET, type, protocol);
}

void CNetworkUtil::CloseSocket(int nSocket) {
  #ifdef WIN32
    ::closesocket(nSocket);
  #else
    ::close(nSocket);
  #endif
}

bool CNetworkUtil::IsLittleEndian()
{
    unsigned short nTest = 0x1234;
    if(*(unsigned char* )&nTest == 0x34)
        return true;
    return false;
}

void CNetworkUtil::SwapByteOrder(void* pData, int nSize)
{
    if(NULL == pData || 0 == nSize)
        return;

    unsigned char* pCh = (unsigned char*)pData;
    int nHalfSize = nSize/2;
    for(int i = 0;i < nHalfSize; i++)
    {
        unsigned char chTmp;
        chTmp = *(pCh + i);
        *(pCh + i) = *(pCh + nSize -1 -i);
        *(pCh + nSize -1 -i) = chTmp;
    }

}
/*
struct hostent {
    char  *h_name;            // official name of host
    char **h_aliases;         // alias list
    int    h_addrtype;        // host address type
    int    h_length;          // length of address
    char **h_addr_list;       // list of addresses
}
#define h_addr h_addr_list[0] // for backward compatibility
*/
struct hostent * CNetworkUtil::GetHostName(const char* szHost)
{
    ASSERT_RET(szHost, NULL);
    struct in_addr sAddr;
    struct hostent*pHost = NULL;

    int nAddr = inet_aton(szHost, &sAddr);
    if( 0 != nAddr)
        pHost = gethostbyaddr(szHost, sizeof(szHost), AF_INET);
    else
        pHost = gethostbyname(szHost);
    return pHost;
}

void CNetworkUtil::PrintAddress(struct hostent*pHost)
{
    ASSERT_RET_VOID(pHost);

    struct in_addr addr;
    char **pp = NULL;
    printf("hostname: %s\n", pHost->h_name);

    for (pp = pHost->h_aliases; *pp != NULL; pp++)
        printf("alias: %s\n", *pp);

    for (pp = pHost->h_addr_list; *pp != NULL; pp++) {
        addr.s_addr = ((struct in_addr *)*pp)->s_addr;
        printf("address: %s\n", inet_ntoa(addr));
    }
}

void CNetworkUtil::ResolveAddress(const char* szHost)
{
    PrintAddress(GetHostName(szHost));
}

int CNetworkUtil::Connect(char *szHost, int nPort)
{
    int clientfd = -1;
    struct sockaddr_in sAddr;

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1; /* Check errno for cause of error */

    if(FillAddress(szHost, nPort, sAddr) < 0)
        return -2;

    /* Establish a connection with the server */
    if (connect(clientfd, (SA *) &sAddr, sizeof(sAddr)) < 0)
        return -1;
    return clientfd;
}

int CNetworkUtil::Listen(int port)
{
    int listenfd, optval=1;
    struct sockaddr_in serveraddr;

    /* Create a socket descriptor */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return -1;

    /* Eliminates "Address already in use" error from bind */
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
           (const void *)&optval , sizeof(int)) < 0)
    return -1;

    /* Listenfd will be an endpoint for all requests to port
       on any IP address for this host */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)port);
    if (bind(listenfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0)
    return -1;

    /* Make it a listening socket ready to accept connection requests */
    if (listen(listenfd, LISTENQ) < 0)
    return -1;
    return listenfd;
}

/* udp_client - set up a UDP client */
SOCKET CNetworkUtil::UdpClient(const char *hname, const char *sname,
	struct sockaddr_in *sap )
{
	SOCKET s;

	SetAddress( hname, sname, sap, "udp" );
	s = socket( AF_INET, SOCK_DGRAM, 0 );
	if ( !isvalidsock( s ) )
		error( 1, errno, "socket call failed" );
	return s;
}

/* udp_server - set up a UDP server */
SOCKET CNetworkUtil::UdpServer(const char *hname, const char *sname )
{
	SOCKET s;
	struct sockaddr_in local;

	SetAddress( hname, sname, &local, "udp" );
	s = socket( AF_INET, SOCK_DGRAM, 0 );
	if ( !isvalidsock( s ) )
		error( 1, errno, "socket call failed" );
	if ( bind( s, ( struct sockaddr * ) &local,
		 sizeof( local ) ) )
		error( 1, errno, "bind failed" );
	return s;
}

/* tcp_server - set up for a TCP server */
SOCKET CNetworkUtil::TcpServer(const char *hname,const char *sname )
{
	struct sockaddr_in local;
	SOCKET s;
	const int on = 1;

	SetAddress( hname, sname, &local, "tcp" );
	s = socket( AF_INET, SOCK_STREAM, 0 );
	if ( !isvalidsock( s ) )
		error( 1, errno, "socket call failed" );

	if ( setsockopt( s, SOL_SOCKET, SO_REUSEADDR,
		( char * )&on, sizeof( on ) ) )
		error( 1, errno, "setsockopt failed" );

	if ( bind( s, ( struct sockaddr * ) &local,
		 sizeof( local ) ) )
		error( 1, errno, "bind failed" );

	if ( listen( s, NLISTEN ) )
		error( 1, errno, "listen failed" );

	return s;
}

/* tcp_client - set up for a TCP client */
SOCKET CNetworkUtil::TcpClient(const char *hname, const char *sname )
{
	struct sockaddr_in peer;
	SOCKET s;

	SetAddress( hname, sname, &peer, "tcp" );
	s = socket( AF_INET, SOCK_STREAM, 0 );
	if ( !isvalidsock( s ) )
		error( 1, errno, "socket call failed" );

	if ( connect( s, ( struct sockaddr * )&peer,
		 sizeof( peer ) ) )
		error( 1, errno, "connect failed" );

	return s;
}

void CNetworkUtil::SetAddress(const char *hname, const char *sname,
	struct sockaddr_in *sap, const char *protocol )
{
	struct servent *sp;
	struct hostent *hp;
	char *endptr;
	short port;

	bzero( sap, sizeof( *sap ) );
	sap->sin_family = AF_INET;
	if ( hname != NULL )
	{
		if ( !inet_aton( hname, &sap->sin_addr ) )
		{
			hp = gethostbyname( hname );
			if ( hp == NULL )
				error( 1, 0, "unknown host: %s\n", hname );
			sap->sin_addr = *( struct in_addr * )hp->h_addr;
		}
	}
	else
		sap->sin_addr.s_addr = htonl( INADDR_ANY );
	port = strtol( sname, &endptr, 0 );
	if ( *endptr == '\0' )
		sap->sin_port = htons( port );
	else
	{
		sp = getservbyname( sname, protocol );
		if ( sp == NULL )
			error( 1, 0, "unknown service: %s\n", sname );
		sap->sin_port = sp->s_port;
	}
}

} /* namespace wfan */
