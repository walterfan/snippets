#include "gmock/gmock.h"
#include "StringUtil.h"
#include <string>
#include <iostream>

using namespace std;
using namespace testing;
using namespace wfan;
using ::testing::Return;
using ::testing::Mock;

const string TEST_MSML_PLAY_START = "<?xml version=\"1.0\" encoding=\"US-ASCII\"?>\r\n"
    "<msml version=\"1.1\">\r\n"
    "<dialogstart target=\"conn:8773a461\" type=\"application/moml+xml\" name=\"ivrWelcome\">\r\n"
    "<play cvd:barge=\"true\" cvd:cleardb=\"true\" iterations=\"1\" >\r\n"
    "<audio uri=\"file://provisioned/customized/tcl/chinese/4100.wav\"/>\r\n"
    "<playexit>\r\n"
    "<send event=\"app.playToCallDone\" namelist=\"play.end play.amt\" target=\"source\"/>\r\n"
    "</playexit>\r\n"
    "</play>\r\n"
    "</dialogstart>\r\n"
    "</msml>\r\n";

TEST(StringUtilTest, strok_r)
{
    cout<<"--- StringTest strok_r --"<<endl;
	
    int in=0;  
    char buffer[]="Fred male 25,John male 62,Anna female 16";  
    char *p[20];  
    char *buf=buffer;  
    char *outer_ptr=NULL;  
    char *inner_ptr=NULL;  
    while((p[in] = strtok_r(buf, ",", &outer_ptr))!=NULL)   
    {  
        buf=p[in];  
        while((p[in]=strtok_r(buf, " ", &inner_ptr))!=NULL)   
        {  
            in++;  
            buf=NULL;  
        }  
        buf=NULL;  
    }  
    printf("Here we have %d strings\n",in);  
    for (int j=0; j<in; j++)  
    {     
        printf("%s\n",p[j]);  
    }  


}


TEST(StringUtilTest, get_value_by_key) {
    string strMsml = TEST_MSML_PLAY_START;
    string strDialogName = "";
    int ret1 = get_value_by_key(strMsml, strDialogName, "name=\"", "\"");
    EXPECT_EQ(ret1, 0);
    EXPECT_EQ("ivrWelcome", strDialogName);


}


TEST(StringUtilTest, replace_value_by_key) {
    //int replace_value_by_key(std::string& strMsml, string mask, const char* key="conn:", const char* sep="/\"");
    string str1 = "id=\"conn:1234abcd/dialog:ivrWelcome\"";
    string str2 = "id=\"conn:1234abcd\" application:ivrWelcome\"";
    int ret = replace_value_by_key(str1, "1111" ,"conn:", "/\"");
    cout<<ret << ": " <<str1<<endl;
    ret = replace_value_by_key(str2, "2222","conn:", "/\"");
    cout<<ret << ": " <<str2<<endl;
    ASSERT_EQ(str1, "id=\"conn:1111/dialog:ivrWelcome\"");
    ASSERT_EQ(str2, "id=\"conn:2222\" application:ivrWelcome\"");
}

