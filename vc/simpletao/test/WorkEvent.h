#ifndef __WORK_EVENT__
#define __WORK_EVENT__

#include <stdint.h>
#include <string>

typedef uint32_t CmResult;

typedef enum {
	SIP,
	SOX,
	XMPP
} EventType;

class CWorkEvent
{
public:
	CWorkEvent(void);
	CWorkEvent(std::string strName);
	virtual ~CWorkEvent(void);
	CmResult GetResult() const
	{ return m_nResult; };
	std::string GetName() const
	{ return m_strName; };
	EventType GetEventType() const
	{ return m_eventType;};
private:
	EventType m_eventType;
	CmResult m_nResult;
	std::string m_strName;
};

class CTransaction
{
public:
	CTransaction();
	virtual ~CTransaction();
};

class IEventAgent
{
public:
    virtual ~IEventAgent() {};
	virtual CmResult SendEvent(EventType eventType, std::string strParam) = 0;
	virtual CWorkEvent* WaitEvent(CTransaction* pTransaction, uint32_t timeout) = 0;
};



class CEventAgent: public IEventAgent
{
public:
	CEventAgent() ;
	virtual ~CEventAgent() ;
	virtual CmResult SendEvent(EventType eventType, std::string strParam);
	virtual CWorkEvent* WaitEvent(CTransaction* pTransaction, uint32_t timeout);
};

class CEventHandler
{
public:
	CEventHandler(CEventAgent* pAgent = NULL);
	virtual ~CEventHandler();

	CmResult HandleEvent(CWorkEvent* pEvent);

private:
	CEventAgent* m_pAgent;
};


class CCallManager
{
public:
	CCallManager();
	virtual ~CCallManager();

	CmResult Initialize();
	CmResult Destroy();
};

#endif