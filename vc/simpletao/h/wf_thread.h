#ifndef __WF_THREAD_H__
#define __WF_THREAD_H__

class IWfEventQueue;

class WF_Thread
{
public:
	WF_THREAD_ID get_thread_id();
	WF_Thread();
	virtual ~WF_Thread();
public:
	WfResult kill();

}


#endif