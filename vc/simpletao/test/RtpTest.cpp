#include "gmock/gmock.h"
#include <string>
#include <iostream>

extern "C" {
#include "srtp.h"
}

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

class CRtpUnitTest: public testing::Test
{
protected:
    CRtpUnitTest() {}
    ~CRtpUnitTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST(CRtpUnitTest, RtpPacketGenerate)
{
	cout<<"--- CRtpUnitTest --"<<endl;
    const char* szTest = "waltertest";

    char* octets = octet_string_hex_string(szTest, strlen(szTest));
    printf("%s\n", octets);
}