#include "TestCase.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
using namespace std;

namespace wfan {


int TestCase::Serialize(std::ostream& os) const {
    Json::Value root;
    root["name"] = name;
    root["feature"] = feature;
    root["scenario"] = scenario;
    root["given"] = given;
    root["when"] = when;
    root["then"] = then;
    root["result"] = result;
    os << root;
    return 0;
}

int TestCase::Deserialize(Json::Value root)  {
    
    this->name = root.get("name", "").asString();
    this->feature = root.get("feature", "").asString();
    this->scenario = root.get("scenario", "").asString();
    this->given = root.get("given", "").asString();
    this->when = root.get("when", "").asString();
    this->then = root.get("then", "").asString();
  
    this->result = root.get("result", false).asBool();
    return 0;
}


std::ostream& operator<<(std::ostream& os, const TestCase& obj) {
    obj.Serialize(os);
    return os;
}


//----------------------------  TestSuite -----------------------------------

int TestSuite::Serialize(std::ostream& os) const {

    std::map<std::string, TestCase>::const_iterator it = testcases.begin();

    for(; it != testcases.end(); ++it )
    {
     TestCase testcase = it->second;
     testcase.Serialize(os);
    }
    return 0;
}

std::ostream& operator<<(std::ostream& os, const TestSuite& obj)  {
    obj.Serialize(os);
    return os;
}

void TestSuite::PutTestCase(string caseName, TestCase testCase) {
    testcases.insert(std::pair<string,TestCase>(caseName,testCase));
}
//----------------------------  TestSuitLoader -----------------------------------


TestSuitLoader::TestSuitLoader(std::string fileName):m_strFileName(fileName) {

}
TestSuitLoader::~TestSuitLoader() {}   

int TestSuitLoader::Load() {
    std::ifstream json_file(m_strFileName.c_str(), std::ifstream::binary);  

    if(!json_file.good())  {
        cerr << m_strFileName<<" read failed" << endl;
        return -1;
    }
    json_file >> m_jsonRoot;

    Json::Value jsonSuites = m_jsonRoot["testsuites"];
    int nSuiteCount = jsonSuites.size();

    for ( int i = 0; i < nSuiteCount; ++i )  {
        Json::Value jsonSuite  = jsonSuites[i];

        TestSuite testSuite;
        testSuite.name = jsonSuite.get("name", "").asString();
        //m_testsuites.insert(std::pair<string,int>('a',100) )
        Json::Value jsonCases = jsonSuite["testcases"];
        int nCaseCount = jsonCases.size();

        for ( int j = 0; j < nCaseCount; ++j )  {
            Json::Value jsonCase  = jsonCases[i];
            //cout<< jsonCase <<endl;
            TestCase testCase;
            
            testCase.Deserialize(jsonCase);

            testSuite.PutTestCase(testCase.name, testCase);

        }
        
    }

    return 0;
}

int TestSuitLoader::Serialize(std::ostream& os) const {
    std::map<std::string, TestSuite>::const_iterator it = m_testsuites.begin();
    for(; it != m_testsuites.end(); ++it )
    {
     TestSuite testsuite = it->second;
     testsuite.Serialize(os);
    }
    return 0;
}

std::ostream& operator<<(std::ostream& os, const TestSuitLoader& obj) {
    obj.Serialize(os);
    return os;
}

const std::map<std::string, TestSuite>& TestSuitLoader::GetTestsuites() const {
    return m_testsuites;
}

 



}//end of namespace
