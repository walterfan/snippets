#include "gmock/gmock.h"
#include <stdint.h>
#include <string>
#include <iostream>
#include <memory>
using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

#define TEST_NAME_TRACE() cout << "#---" << m_strTestName << "---" << endl
#define FINGERPRINT 0xffff
static long snTestNum = 0;

struct Packet
{
    uint32_t fingerprint;
    uint32_t sn;

    Packet(uint32_t seqNum): fingerprint(FINGERPRINT),sn(seqNum)      
    { std::cout << "Packet::Packet " << sn <<endl;  }
    ~Packet()     
    { std::cout << "Packet::~Packet " << sn << endl; fingerprint = 0;}
    uint32_t GetSN() 
    { std::cout << "Packet::GetSN " << sn << endl; return sn; }


};


class SmartPtrTest : public testing::Test
{
public:
    SmartPtrTest(): m_strFeature("Smart Pointer"), m_strTestName("") {

    }
    virtual ~SmartPtrTest() { }

    virtual void SetUp() {


    }
    virtual void TearDown()  {} 

    virtual void RecordTestCase(string given, string when, string then, string scenario="", string checkpoints="") {
        string strClassName(::testing::UnitTest::GetInstance()->current_test_info()->test_case_name());
        string strFuncName(::testing::UnitTest::GetInstance()->current_test_info()->name());
        string strTestName = strClassName + "." + strFuncName;
        cout << "#---" << strTestName << "---" << endl;

        RecordProperty("feature", m_strFeature);
        RecordProperty("scenario", scenario.empty()?strTestName:scenario);
        RecordProperty("given", given);
        RecordProperty("when", when);
        RecordProperty("then", then);
        RecordProperty("checkpoints", checkpoints);
    }
protected:
    string m_strFeature;
    string m_strTestName;

};

uint32_t GetFingerprint(Packet* pPacket)
{
    std::cout << "Packet* pPacket address=" << pPacket << endl;
    uint32_t* pFingerprint = (uint32_t*)pPacket;
    printf("fingerprint=%d\n", *pFingerprint);
    return *pFingerprint;
}

TEST_F(SmartPtrTest, AutoPtrTest)
{
   RecordTestCase("create a pointer to auto_ptr", "out of the scope", "the pointer will be released");
   Packet* p0 = new Packet(++snTestNum);
   {
       auto_ptr<Packet> p1(p0);
       p1 -> GetSN();
       ASSERT_EQ(GetFingerprint(p0), FINGERPRINT);
   }
   ASSERT_NE(GetFingerprint(p0), snTestNum);

}

TEST_F(SmartPtrTest, UniquePtrTest)
{
   RecordTestCase("create a pointer to unique_ptr", "out of the scope", "the pointer will be released");
	
    Packet* p0 = new Packet(++snTestNum);
    {
        std::unique_ptr<Packet> p1(p0);  // p1 owns Packet
        if (p1) p1->GetSN();
     
        {
            std::unique_ptr<Packet> p2(std::move(p1));  // now p2 owns Packet, p1 contain a null pointer
            ASSERT_FALSE(p1);
            ASSERT_EQ(GetFingerprint(p2.get()), FINGERPRINT);
            
            p1 = std::move(p2);  // ownership returns to p1
            cout << "destroying p2..." << endl;
        }
     
        if (p1) p1->GetSN();
    }
    ASSERT_NE(GetFingerprint(p0), snTestNum);

}

TEST_F(SmartPtrTest, SharedPtrTest)
{
    RecordTestCase("create a pointer to shared_ptr", "out of the scope", "the pointer will be released");
    Packet* p0 = new Packet(++snTestNum);
    {
        std::shared_ptr<Packet> p1(p0);
        {
            std::shared_ptr<Packet> p2 = p1;
        }
    }
}

TEST_F(SmartPtrTest, WeakPtrTest)
{
    RecordTestCase("create a pointer to weak_ptr", "out of the scope", "the pointer will be released");
    Packet* p0 = new Packet(++snTestNum);
  
    std::shared_ptr<Packet> ps(p0);
    std::weak_ptr<Packet> pw = ps;

    std::cout << "sn == " << ps->GetSN() << ": ";
    if (auto spt = pw.lock()) { // Has to be copied into a shared_ptr before usage
        std::cout << spt->GetSN() << endl;
    }
    else {
        std::cout << "gw is expired"<< endl;
    }
}


