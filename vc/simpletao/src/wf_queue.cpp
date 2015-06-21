#include "common.h"
#include "wf_queue.h"

template<class T>
WF_Queue<T>::WF_Queue():
	m_uHead(0),
	m_uTail(0),
	m_uMaxSize(0),
	m_pData(NULL)
{

}

template<class T>
WF_Queue<T>::WF_Queue(uint32_t nMaxSize):
	m_uHead(0),
	m_uTail(0),
	m_uMaxSize(nMaxSize),
	m_pData(NULL)
{
	m_pData = new T[nMaxSize + 1]
}