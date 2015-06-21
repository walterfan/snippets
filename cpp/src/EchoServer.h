/*
 * EchoServer.h
 *
 *  Created on: Aug 4, 2013
 *      Author: walter
 */

#ifndef _WF_ECHOSERVER_H_
#define _WF_ECHOSERVER_H_

#include "wf_common.h"
#include "NetworkUtil.h"

enum ConnectionStatus {
	CONN_FAILED
	CONN_ESTABLISHED,
	CONN_CLOSING,
	CONN_CLOSED
};

struct ConnectionAddr
{
	std::string strHost,
	uint32_t nPort
};

class IEchoServer 
{
public:
	virtual error_t Start(ConnectionAddr sAddr) = 0;
	virtual void Stop() = 0;

};

class CEchoClient
{
public:
    virtual error_t Connect(ConnectionAddr sAddr);
    virtual error_t OnConnect(ConnectionStatus kStatus, ConnectionAddr sLocalAddr);
    virtual uint32_t SendMessage(const char* szData, uint32_t nSize = 0);
};


class CEchoServer
{
public:
	virtual error_t Start(ConnectionAddr sAddr);
	virtual void Stop();

	virtual error_t OnConnect(ConnectionStatus kStatus, ConnectionAddr sRemoteAddr);
	virtual void OnMessage(const char* szData, uint32_t nSize = 0);
	virtual uint32_t SendMessage(const char* szData, uint32_t nSize = 0);
	
};

#endif /* ECHOSERVER_H_ */
