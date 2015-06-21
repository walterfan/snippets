#include "Message.h"

CFolder::CFolder():messages()
{

}

CFolder::~CFolder()
{

}


void CFolder::add_msg(CMessage* msg)
{
	messages.insert(msg);
}
void CFolder::remove_msg(CMessage* msg)
{
	messages.erase(msg);
}


CMessage::~CMessage(void)
{

}

CMessage::CMessage(const CMessage &msg):contents(msg.contents), folders(msg.folders)
{
	put_msg_in_folders(folders);
}

void CMessage::put_msg_in_folders(const std::set<CFolder*> &rhs) 
{
	for(std::set<CFolder*>::const_iterator beg = rhs.begin();
		beg != rhs.end(); ++beg)
		(*beg)->add_msg(this);
}
void CMessage::remove_msg_from_folders() 
{
	for(std::set<CFolder*>::const_iterator beg = folders.begin();
		beg != folders.end(); ++beg)
		(*beg)->remove_msg(this);
}