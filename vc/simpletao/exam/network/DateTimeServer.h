#ifndef _DATE_TIME_SERVER_H
#define _DATE_TIME_SERVER_H

#include "ace/FILE_IO.h"
#include "ace/SOCK_Acceptor.h"

class CDateTimeServer
{
public:
	CDateTimeServer(void);
	~CDateTimeServer(void);
public:
  // Template Method that runs logging server's event loop.
  virtual int run (int argc, char *argv[]);
   // Accessor.
  ACE_SOCK_Acceptor &acceptor () { return acceptor_; }

private:
  ACE_SOCK_Acceptor acceptor_; // Socket acceptor endpoint.
};

#endif