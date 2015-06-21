#pragma once

#ifndef CMESSAGE_H_
#define CMESSAGE_H_
#include <string>
#include <set>

class CMessage;

class CMessageServer
{
public:
	CMessageServer();
	virtual~ CMessageServer();
	virtual int set_option(char* name, char* value);
	virtual int init(int argc, char* argv[]);
	virtual int clean();
	
	virtual int start();
	virtual int stop();

	virtual int run();
	virtual int join();
	
};

class CMessageClient
{
public:
	CMessageClient();
	virtual ~ CMessageClient();

	virtual int init(int argc, char* argv[]);
	virtual int clean();


};

class CFolder 
{
public:
	CFolder();
	~CFolder();
	void add_msg(CMessage* msg);
	void remove_msg(CMessage* msg);
private:
	std::set<CMessage*> messages;
};


class CMessage
{
public:
	~CMessage(void);

	CMessage(const std::string &str=""):contents(str) {}
	CMessage(const CMessage&);
	CMessage& operator=(const CMessage&);

private:
	std::string contents;
	std::set<CFolder*> folders;
	void put_msg_in_folders(const std::set<CFolder*>&);
	void remove_msg_from_folders();
};

#endif