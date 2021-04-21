#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

#include "boost/function.hpp"
#include "boost/bind.hpp"
#include <boost/thread/thread.hpp>

namespace
{
  void OnExecute(int param1, float param2, int param3)  { 
      printf("1) OnExecute: %d, %f, %d\n", param1, param2, param3);
  }

  void OnExecute(int param) { 
      printf("2) OnExecute: %d\n", param); 
  }

  void OnExecute(float param) { 
      printf("3) OnExecute: %f\n", param); 
  }

  class CTask
  {
  public: // interface
    void OnExecute(float param) { 
        printf("4) OnExecute: %f\n", param);
    }

    void OnExecute(int param) {
        printf("5) OnExecute: %d\n", param);
    }
  };

  void print_user_detail(int age, float salary, std::string name)
  {
    std::cout << "name: " << name 
              << ", age: " << age 
              << ", salary: " << salary
              << std::endl;
  }

class CTaskExecutor
{  
public:  
    void Execute()  
    {  
        std::cout<<"CTaskExecutor::Execute"<<std::endl;  
    }  
    void start()  
    {  
        boost::function0<void> f = boost::bind(&CTaskExecutor::Execute, this);  
        boost::thread thrd(f);  
        thrd.join();  
    }  
};  

} // namespace




TEST(BoostTest, function_bind_test)
{
  cout<<"--- BoostTest, bind --"<<endl;

  // non-member
  boost::function<void(int, float, int)> func1 = boost::bind(::OnExecute, _1, _2, _3); // can bind normally
  func1(2,3.3,4);
  typedef void (*NonMemberFuncType)(int);
  boost::function<void(int)>  func2 = boost::bind(static_cast<NonMemberFuncType>(::OnExecute), _1);
  func2(123);
  
  // member
  CTask* objPtr = new CTask();
  typedef void (CTask::*OverloadFuncType)(float);
  boost::function<void(float)>  func3 = boost::bind(static_cast<OverloadFuncType>(&CTask::OnExecute), objPtr, _1);
  func3(3.45);
}

TEST(BoostTest, print_user_detail)
{
    // declare function pointer variables
    boost::function<void(std::string, float, int)> shuffleFunction;
    boost::function<void(void)> voidFunction;
    boost::function<void(float)> reducedFunction;

    // bind the methods
    shuffleFunction = boost::bind(::print_user_detail, _3, _2, _1);
    voidFunction = boost::bind(::print_user_detail, 25, 20005.f, "Alice");
    reducedFunction = boost::bind(::print_user_detail, 30, _1, "Bob");

    // call the bound functions
    shuffleFunction("Walter", 1000.10f, 20);
    voidFunction();
    reducedFunction(35000.f);

} 


TEST(BoostTest, thread)
{
    CTaskExecutor executor;  
    executor.start();  
  
    system("sleep 1");  

}

