#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

TEST(StlTest, StringTest)
{
	cout<<"--- StringTest --"<<endl;
    string strTransaction = "APP|APP_AUTHENTICATE_RESPONSE|0|3";
    ASSERT_TRUE(strTransaction.find("APP|APP_AUTHENTICATE_RESPONSE|0|") != string::npos);
}