#include "gmock/gmock.h"
#include "StringUtil.h"
#include <sys/types.h>
#include <regex.h>
#include <stdio.h>

#include <string>
#include <iostream>

using namespace std;
using namespace testing;
using namespace wfan;
using ::testing::Return;
using ::testing::Mock;

//refer to http://pubs.opengroup.org/onlinepubs/009695399/functions/regcomp.html
bool match(const char *string, const char *pattern)
{
    int    status;
    regex_t    re;


    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        return false;
    }
    status = regexec(&re, string, (size_t) 0, NULL, 0);
    regfree(&re);
    if (status != 0) {
        return false;  
    }
    return true;
}


const string TEST_STR1 = "<?xml version=\"1.0\" encoding=\"US-ASCII\"?>\r\n"
    "<msml version=\"1.1\">\r\n"
    "<dialogstart target=\"conn:8773a461\" type=\"application/moml+xml\" name=\"ivrWelcome\">\r\n"
    "<play cvd:barge=\"true\" cvd:cleardb=\"true\" iterations=\"1\" >\r\n";

const string TEST_STR2 = "<?xml version=\"1.0\" encoding=\"US-ASCII\"?>\r\n"
    "<app>\r\n"
    "xxxAction=JoinConference\r\n"
    "</app>";




TEST(RegexTest, TEST_STR1) {
    string regex_str1 = ".*dialogstart.*ivrWelcome.*";
    string regex_str2 = ".*dialogstart.*ivrwelcome.*";
    
    ASSERT_TRUE(match(TEST_STR1.c_str(), regex_str1.c_str()));
    ASSERT_FALSE(match(TEST_STR1.c_str(), regex_str2.c_str()));
}

TEST(RegexTest, TEST_STR2) {
    string regex_str1 = "Action=JoinConference";
    string regex_str2 = ".*Action=JoinConference.*";
    
    ASSERT_TRUE(match(TEST_STR2.c_str(), regex_str1.c_str()));
    //ASSERT_FALSE(match(TEST_STR2.c_str(), regex_str2.c_str()));
}

