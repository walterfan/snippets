/*
 * EchoServer.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: walter
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "EchoServer.h"

int CEchoClient::Connect(ConnectionAddr sAddr)
{
    return NetworkUtil::Connect(sAddr.strHost.c_str(), sAddr.nPort);
}

CEchoServer::CEchoServer() {
	// TODO Auto-generated constructor stub

}

CEchoServer::~CEchoServer() {
	// TODO Auto-generated destructor stub
}

