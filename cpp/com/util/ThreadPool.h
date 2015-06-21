#ifndef __WF_THREAD_POOL__
#define __WF_THREAD_POOL__

#include <stdint.h>

#include "boost/function.hpp"
#include "boost/bind.hpp"
#include "boost/thread/thread.hpp"

class IThreadPool
{
public:
	virtual int Start() = 0;
	virtual int Stop()  = 0;

	
};


#endif
