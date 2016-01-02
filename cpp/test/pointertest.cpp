#include "gmock/gmock.h"
#include <string>
#include <iostream>
#include <pthread.h>

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;



void print_address(const char* prompt, void *pAddr)
{
        printf("%s address: %x\n", prompt, pAddr);
}

class IRunnable {
public:
	virtual void run() = 0;
    virtual ~IRunnable() {}
};

class ICallable {
public:
	virtual void* call(void* pParam) = 0;
    virtual ~ICallable() {}
};

class CThreadTask: public IRunnable, public ICallable
{
public:
	CThreadTask() {
        m_thread_id = pthread_self();
		print_address("CThreadTask construct ",this);	
	}
    virtual ~CThreadTask() {
		print_address("CThreadTask destruct ",this);  
	}
	virtual void run() {
		print_address("CThreadTask run ",this);
	}
	virtual void* call(void* pParam) {
		print_address("CThreadTask call ",this);
        return NULL;
	}
protected:
    pthread_t m_thread_id;
};

class CJobTask {
public:
    CJobTask():m_job_count(0) {}
    void on_timer(long timestamp, void* pParam)
    {
        cout <<"CJobTask on_timer @"<<this<<endl;
        ++m_job_count;
    }
    virtual ~CJobTask() {}
protected:
    long m_job_count;
};

class CThreadJob: public CThreadTask, public CJobTask
{
public:

    typedef void  (CThreadTask::*FnRunPtr)(void);    
    typedef void* (CThreadTask::*FnCallPtr)(void*);
    typedef void  (CJobTask::* FnOnTimerPtr)(long timestamp, void* pParam);
    typedef void  (CThreadJob::*FnDumpPtr)(void);


    CThreadJob(const char* szJob): m_job_name(szJob) {}

    void dump() {
        printf("--- CThreadJob::dump ---, m_job_name size = %d\n", sizeof(m_job_name));
        print_address("CThreadJob::this", (CThreadJob*)this);
        print_address("CThreadTask::this", (CThreadTask*)this);
        print_address("CJobTask::this", (CJobTask*)this);
        print_address("IRunnable::this", (IRunnable*)this);
        print_address("ICallable::this", (ICallable*)this);
        
        FnRunPtr pFn      = &CThreadTask::run; 
        FnCallPtr pFnCall = &CThreadTask::call;
        FnOnTimerPtr pFnOnTimer = &CJobTask::on_timer;
        FnDumpPtr pFnDump       = &CThreadJob::dump;

        print_address("CThreadTask::run()",   *((void**)&pFn));
        print_address("CThreadTask::call()",  *((void**)&pFnCall));
        print_address("CJobTask::on_timer()", *((void**)&pFnOnTimer));
        print_address("CThreadJob::dump()",   *((void**)&pFnDump));

        print_address("m_thread_id", &m_thread_id);
        print_address("m_job_count", &m_job_count);
        print_address("m_job_name", &m_job_name);
    }

    virtual ~CThreadJob() {}
private:
    string m_job_name;
};

typedef struct person {
    int age;
    char sex;
} person_t;

person_t walter = {38, 'm'};
person_t alice = {35, 'f'};

int update_person(person** ppPerson, int* pAge)
{
    if(*pAge > 26)
        *ppPerson = &walter;
    else
        *ppPerson = &alice;
    *pAge = (*ppPerson)->age;
    return *pAge;
}


TEST(PointerTest, pointponter)
{
    cout<<"--- PointerTest, pointponter --"<<endl;

    person_t* pPerson = NULL;
    int age = 36;
    update_person(&pPerson, &age);

    cout<<"person="<<pPerson->sex<<endl;
    cout<<"age="<<age<<endl;

}

TEST(PointerTest, ClassAddress) {
    size_t nPtrSize = sizeof(void*);
    size_t nThreadIdSize = sizeof(pthread_t);
    size_t nLongSize = sizeof(long);
    printf("pointer size=%d, pthread_t size=%d, long type size=%d\n", nPtrSize, nThreadIdSize, nLongSize);
    CThreadTask* pTask = new CThreadTask();
    print_address("pTask", pTask);
    IRunnable* pRunnable = pTask;
    print_address("pRunnable", pRunnable);
    pRunnable->run();
    ICallable* pCallable = pTask;
    print_address("pCallable", pCallable);
    int a = 3;
    pCallable->call(&a);
    delete pTask;
    CThreadJob* pJob = new CThreadJob("TestJob");
    pJob->dump();
    delete pJob;
}
