#ifndef __WFAN_TEST_CASE_H__
#define __WFAN_TEST_CASE_H__

#include <iostream>
#include <string>
#include <map>
#include "json/json.h"

namespace wfan {

struct TestCase {   
    std::string name;
    std::string feature;
    std::string scenario;
    std::string given;
    std::string when;
    std::string then;
    bool result;

    int Serialize(std::ostream& os) const;
    int Deserialize(Json::Value root) ;
    friend std::ostream& operator<<(std::ostream&, const TestCase& obj);

};

struct TestSuite {
    std::string name;
    std::map<std::string, TestCase> testcases;

    void PutTestCase(std::string caseName, TestCase testCase);
    int Serialize(std::ostream& os) const;


    friend std::ostream& operator<<(std::ostream&, const TestSuite& obj);
  

};

class TestSuitLoader {
public:
    TestSuitLoader(std::string fileName);
    virtual ~TestSuitLoader();    

    int Load();
    
    int Serialize(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream&, const TestSuitLoader& obj);

    const std::map<std::string, TestSuite>& GetTestsuites() const;

private:
    Json::Value m_jsonRoot; 
    std::string m_strFileName;
    std::map<std::string, TestSuite> m_testsuites;
};


}//end of namespace
#endif