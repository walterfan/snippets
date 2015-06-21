#include "WorkEvent.h"
#include <string>
#include <iostream>

using namespace std;


CWorkEvent::CWorkEvent(void):m_eventType(SIP), m_nResult(0), m_strName("")
{
	cout<<"create CWorkEvent"<<endl;
}

CWorkEvent::CWorkEvent(std::string name):m_eventType(SIP), m_nResult(0), m_strName(name)
{
	cout<<"create CWorkEvent"<<endl;
}

CWorkEvent::~CWorkEvent(void)
{
	cout<<"release CWorkEvent"<<endl;
}

CEventAgent::CEventAgent(void)
{
	cout<<"create CEventAgent"<<endl;
}


CEventAgent::~CEventAgent(void)
{
	cout<<"release CEventAgent"<<endl;
}

CmResult CEventAgent::SendEvent(EventType eventType, std::string strParam)
{
	cout<<"CEventAgent::SendEvent "<<eventType<<", param="<<strParam<<endl;
	return 0;
}

CWorkEvent* CEventAgent::WaitEvent(CTransaction* pTransaction, uint32_t timeout)
{
	cout<<"CEventAgent::WaitEvent "<<pTransaction<<", timeout="<<timeout<<endl;
	return NULL;

}

CEventHandler::CEventHandler(CEventAgent* pAgent): m_pAgent(pAgent)
{
	cout<<"create CEventHandler"<<endl;
}

CEventHandler::~CEventHandler()
{
	cout<<"release CEventHandler"<<endl;
}

CmResult CEventHandler::HandleEvent(CWorkEvent* pEvent)
{
	cout<<"CEventHandler::HandleEvent"<<endl;
	CmResult ret = 0;
	if(!pEvent) {
		return -1;	
	}
	if(m_pAgent) {
		ret = m_pAgent->SendEvent(pEvent->GetEventType(), pEvent->GetName());
		cout<<"CEventHandler::HandleEvent--SendEvent return "<<ret<<endl;
	}
	return ret;
}

