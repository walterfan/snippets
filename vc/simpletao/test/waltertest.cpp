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
#include "ace/Addr.h"
#include "ace/Thread_Manager.h"
#include "wf_define.h"
#include "wf_macro.h"
#define BUFLEN 64
using namespace std;

ACE_THR_FUNC_RETURN thread_func (void *arg)
{
	printf("execute thread_func\n");
	return 0;
}

int thread_test(int argc, char *argv[])
{
	ACE_Thread_Manager* pThMgr = ACE_Thread_Manager::instance();
	ACE_thread_t thId = 0;
	int ret = pThMgr->spawn(thread_func, "create thread"
		, THR_DETACHED|THR_SCOPE_SYSTEM
		, &thId);
	printf("thread_id=%d\n", thId);
	ret = pThMgr->join(thId);
	return ret;
}


int iotest(int argc, char *argv[])
{
	int nRet = 0;
	int ch = 0;
	FILE* fp = NULL;
	char szDataFile[BUFLEN] = "makefile";

/*	for(int i=0;i<argc;i++)
	{
		msg_trace(argv[i]);
	}*/
	msg_trace("--- Walter test program ---");
	if(argc>1) {
		size_t nLen = strlen(argv[1]);
		if(nLen >= BUFLEN) {
			nLen = BUFLEN - 1;
		}
		strncpy(szDataFile, argv[1], nLen);
	}

	if((fp = fopen(szDataFile,"r"))==NULL)
	{
		err_trace("error to open file" << szDataFile);
		nRet = -1;
		goto WF_EXIT;
	}

	ch = getc( fp );
	PRINT_HEX(ch);
	while( ch != EOF && ch != '\n') {
	     putc( ch, stdout );
	     ch = getc( fp );
	}

	fclose(fp);
WF_EXIT:
	putc('\n', stdout);
	msg_trace("--- end ---");
	return nRet;


}

