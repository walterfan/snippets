#include "WorkEvent.h"
#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

class MockEventAgent: public CEventAgent
{
public:
	MOCK_METHOD2(SendEvent, CmResult(EventType eventType, std::string strParam));
	MOCK_METHOD2(WaitEvent, CWorkEvent*(CTransaction* pTransaction, uint32_t timeout));
};


TEST(EventHandlerTest, HandleEventTest)
{
	cout<<"--- HandleEventTest --"<<endl;
	CWorkEvent* pEvent = new CWorkEvent("testEvent");
	
	MockEventAgent* pAgent = new MockEventAgent();
    
    ON_CALL(*pAgent,SendEvent(_,_)).WillByDefault(Return(2));

    EXPECT_CALL(*pAgent, SendEvent(_,_)).WillOnce(Return(2));

	CEventHandler* pHandler = new CEventHandler(pAgent);	
	
	CmResult ret = pHandler->HandleEvent(pEvent);
	
	EXPECT_EQ(ret, 2);
	
    Mock::VerifyAndClear(pAgent);
	
	delete pHandler;
	delete pAgent;
	delete pEvent;
    
}