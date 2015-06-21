/****************************************************************************
* Copyright  2005 JinWei Bird Studio.	All rights reserved
*
* Filename: wf_xxx.cpp
* Description: cpp test file
*
* Version:1.0
* Create date: 05/03/2007
* Author: walter.fan@gmail.com
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "ace/OS_NS_sys_time.h"
#include "ace/CDR_Stream.h"
#include "ace/INET_Addr.h"
#include "ace/SOCK_Connector.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Stream.h"
#include "ace/Log_Msg.h"
#include "ace/Log_Record.h"
#include "ace/Truncate.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_stdlib.h"
#include "ace/streams.h"

#define BUFLEN 64
using namespace std;

const unsigned int BUFSIZE = 1024;

int ace_webcli_test(int argc, char *argv[])
{
	//DateTimeServer* pSvr = new DateTimeServer();
	const char* path 
		= argc > 1? argv[1]: "/forecastrss?w=12712552&u=c";
	const char* host
		= argc > 2? argv[2]: "xml.weather.yahoo.com";
	int port = argc > 3?
		atoi(argv[3]):80;
	cout<<"Get "<<host<<path<<endl;

	ACE_SOCK_Connector connector;
	ACE_SOCK_Stream peer;
	ACE_INET_Addr addr;

	ACE_Time_Value timeout(10);

	ACE_ASSERT(addr.set(port, host) != -1);

	ACE_ASSERT(connector.connect(peer, addr,&timeout) != -1);

	char buf[BUFSIZE];
	iovec iov[3];
	iov[0].iov_base="GET ";
	iov[0].iov_len = 4;
	iov[1].iov_base=(char*)path;
	iov[1].iov_len = strlen(path);
	iov[2].iov_base=" HTTP/1.0\r\n\r\n";
	iov[2].iov_len = 13;
	
	
	ACE_ASSERT(peer.sendv_n(iov, 3) != -1);

	
	while(true)
	{
		ssize_t n = peer.recv(buf, sizeof(buf), &timeout);
		if (n > 0) {
			ACE::write_n(ACE_STDOUT, buf, n);
		}
		else {
			break;
		}
	}
	return peer.close() == -1? -4:0;
}


int ace_svr_test(int argc, char *argv[])
{
  ACE_INET_Addr port_to_listen (8080);
  ACE_SOCK_Acceptor acceptor;

  if (acceptor.open (port_to_listen, 1) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%p\n"),
                       ACE_TEXT ("acceptor.open")),
                      100);

  /*
   * The complete open signature:
   *
  int open (const ACE_Addr &local_sap,
            int reuse_addr = 0,
            int protocol_family = PF_INET,
            int backlog = ACE_DEFAULT_BACKLOG,
            int protocol = 0);
   *
   */

  while (1)
    {
      ACE_SOCK_Stream peer;
      ACE_INET_Addr peer_addr;
      ACE_Time_Value timeout (10, 0);

      /*
       * Basic acceptor usage
       */
#if 0
      if (acceptor.accept (peer) == -1)
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("(%P|%t) Failed to accept ")
                           ACE_TEXT ("client connection\n")),
                          100);
#endif /* 0 */

      if (acceptor.accept (peer, &peer_addr, &timeout, 0) == -1)
        {
          if (ACE_OS::last_error() == EINTR)
            ACE_DEBUG ((LM_DEBUG,
                        ACE_TEXT ("(%P|%t) Interrupted while ")
                        ACE_TEXT ("waiting for connection\n")));
          else
            if (ACE_OS::last_error() == ETIMEDOUT)
              ACE_DEBUG ((LM_DEBUG,
                          ACE_TEXT ("(%P|%t) Timeout while ")
                          ACE_TEXT ("waiting for connection\n")));
        }
      else
        {
          ACE_TCHAR peer_name[1042];
          peer_addr.addr_to_string (peer_name, 1042);
          ACE_DEBUG ((LM_DEBUG,
                      ACE_TEXT ("(%P|%t) Connection from %s\n"),
                      peer_name));
          char buffer[4096];
          ssize_t bytes_received;

          while ((bytes_received =
                    peer.recv (buffer, sizeof(buffer))) != -1)
            {
              peer.send_n (buffer, bytes_received);
            }

          peer.close ();
        }
    }

  return (0);
}
