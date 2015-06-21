#include "ace/OS.h"
#include "ace/Message_Block.h"

#include "gmock/gmock.h"
#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>

using namespace std;
using namespace testing;

const unsigned int BUFSIZE = 10;

TEST(AceTest, MessageBlock)
{
	ACE_Message_Block *pHead = new ACE_Message_Block(BUFSIZE);
	ACE_Message_Block *pMb = pHead;
		
	for(int i=0;i<3;i++)
	{
		ssize_t nBytes = ACE_OS::read_n(ACE_STDIN, pMb->wr_ptr(), pMb->size());
		cout<<"read: "<<nBytes<<endl;
		if(nBytes <= 0 )
			break;
		//move the write pointer to the end of buffer
		pMb->wr_ptr(nBytes);
		//allocate a new MB and link to end of list
		pMb->cont(new ACE_Message_Block(BUFSIZE));
		pMb = pMb->cont();
	}
	
	//const char* szData = "waltertest";
	//pHead->copy(szData);
	for(pMb = pHead; pMb != NULL; pMb = pMb->cont())
	{
		ACE_OS::write_n(ACE_STDOUT, pMb->rd_ptr(), pMb->length());
	}
	pHead->release();
}

