#ifndef WF_QUEUE_H
#define WF_QUEUE_H

#include <stdint.h>

template<class T> 
class WF_Queue {
public:
	WF_Queue();
	WF_Queue(uint32_t uMaxSize);
	virtual ~WF_Queue();

	int Enqueue(T &data);
	int Dequeue(T &data);
	bool IsEmpty();
	bool IsFull();
private:
	uint32_t m_uHead;
	uint32_t m_uTail;
	uint32_t m_uMaxSize;
	T * m_pData;
};

#endif