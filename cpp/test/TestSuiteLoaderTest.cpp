#include <fstream>
#include <iostream>
#include "gtest/gtest.h"
#include "json/json.h"
#include "TestCase.h"

using namespace std;
using namespace testing;
using namespace wfan;

class TestSuitLoaderTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    cout<< "-- TestSuitLoaderTest SetUp --" << endl;
    m_pLoader = new TestSuitLoader("./dat/login_test_cases.json");

  }

  virtual void TearDown() {
    cout<< "-- TestSuitLoaderTest TearDown --" << endl;
    if(m_pLoader) {
        delete m_pLoader;
        m_pLoader = NULL;
    }
  }

  TestSuitLoader* m_pLoader;
};

class TestSuitLoaderImplTest : public TestSuitLoaderTest {
public:
    virtual void SetUp() {
      TestSuitLoaderTest::SetUp();
      cout<< "-- TestSuitLoaderImplTest SetUp --" << endl;
    }
    virtual void TearDown() {
      TestSuitLoaderTest::TearDown();
      cout<< "-- TestSuitLoaderImplTest TearDown --" << endl;
    }
};


TEST_F(TestSuitLoaderTest, LoadTest) {
  cout << "TestSuitLoaderTest.LoadTest" <<endl;
  int ret = m_pLoader->Load();
  EXPECT_EQ(ret , 0);

  

  map<string, TestSuite> testSuites = m_pLoader->GetTestsuites();
  std::map<std::string, TestSuite>::const_iterator it = testSuites.begin();

    for(; it != testSuites.end(); ++it )
    {
     TestSuite suite = it->second;
     suite.Serialize(cout);
    }
  
}

TEST_F(TestSuitLoaderImplTest, ParseTest) {
  cout << "TestSuitLoaderImplTest.ParseTest" <<endl;
}
