#include <fstream>
#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "json/json.h"
#include "TestCase.h"

using namespace std;
using namespace testing;

struct User {
    User(string strName, string strEmail, int nAge): name(strName), email(strEmail), age(nAge)
     {}
    string name;
    string email;
    int age;

    Json::Value toJson() {
            Json::Value root;
            root["name"] = name;
            root["email"] = email;
            root["age"] = age;
            return root;
        }
};

TEST(JsonCppTest, VectorToJson)
{
    cout<<"--- JsonCppTest.VectorToJson --"<<endl;

    vector<User> users;
    users.push_back(User("ff", "ff@sina.com" ,3 ));
    users.push_back(User("xx", "xx@sina.com" ,10 ));
    
    Json::Value root; 
    Json::Value arr;
    arr.append(users[0].toJson());
    arr.append(users[1].toJson());

    root["users"] = arr;

    cout<< root <<endl;
}

TEST(JsonCppTest, JsonFileRead)
{
    cout<<"--- JsonCppTest.JsonFileRead --"<<endl;
    
    Json::Value root; 

    std::ifstream json_file("./dat/login_test_cases.json", std::ifstream::binary);    
    json_file >> root;

    Json::Value jsonSuites = root["testsuites"];
    //cout<< jsonSuites <<endl;
    int nSuiteCount = jsonSuites.size();
    ASSERT_TRUE(nSuiteCount > 0);
    Json::Value jsonSuite  = jsonSuites[0];

    EXPECT_EQ(jsonSuite.get("name", "").asString(), "login_module_test") << "test suite name is not login_module_test ";
    

    const Json::Value jsonCases = jsonSuite["testcases"];
    int nCaseCount = jsonCases.size();
    ASSERT_TRUE(nCaseCount > 0);

    for ( int i = 0; i < nCaseCount; ++i )  {
        Json::Value jsonCase  = jsonCases[i];

        cout<< jsonCase <<endl;
        EXPECT_EQ(jsonCase["feature"].asString(), "login") << "feature is not login ";
    }
}



