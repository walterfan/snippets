#include "run_example.h"

using namespace std;


int rvalue_demo(int argc, char* argv[])
{
    //move constructor
    Command cmd1(Command("c1"));
    //copy constructor
    Command cmd2 = cmd1;

    shared_ptr<Command> sharedPtr = make_shared<Command>("update");
    sharedPtr->setParameter("user", "alice");
    uint8_t nBytes[3]   = { 0x00,0x01,0x02 };
    sharedPtr->setData(nBytes, 3);
    
    shared_ptr<Command> sharedPtr2 = sharedPtr;
    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__ << ". sharedPtr=" << sharedPtr.get() << ", "<< sharedPtr.use_count() <<", command="<< *sharedPtr;
    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__ << ". sharedPtr2=" << sharedPtr2.get() << ", "<< sharedPtr2.use_count() <<", command="<< *sharedPtr2;

    return 0;
}

int smart_ptr_demo(int argc, char* argv[])
{

    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__ << " -- unique_ptr --";
    //unique_ptr<Command> ptr = unique_ptr<Command>(new Command());
    unique_ptr<Command> uniquePtr = my_make_unique<Command>();
    uniquePtr->setName("create");
    uniquePtr->setParameter("user", "walter");
    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__ << ". unique pointer=" << uniquePtr.get() <<", command="<< *uniquePtr;

    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__ << ". -- shared_ptr --";

    shared_ptr<Command> sharedPtr = make_shared<Command>();
    sharedPtr->setName("retrieve");
    sharedPtr->setParameter("user", "walter");
    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__ << ". shared pointer=" << sharedPtr.get() << ", "<< sharedPtr.use_count() <<", command="<< *sharedPtr;


    return 0;
}
