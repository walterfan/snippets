#include "gmock/gmock.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <future>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
using namespace testing;

std::mutex g_display_mutex;
//./bin/unittest --gtest_filter=FutureTest*

void print_thread_id() {
    std::thread::id this_id = std::this_thread::get_id(); 
    g_display_mutex.lock();
    std::cout << "threadId=" << this_id << endl;
    g_display_mutex.unlock();
}
/*

enum class launch :  {
    async,//a new thread is launched to execute the task asynchronously
    deferred,//the task is executed on the calling thread the first time its result is requested (lazy evaluation)
};

future state:

1. deffered：异步操作还没有开始；
2. ready：异步操作已经完成；
3. timeout：异步操作超时。
*/
int fab(int n) {
    print_thread_id();

	//system_clock::time_point start = system_clock::now();
    if(n == 0 || n == 1) {
        return 1;
    }
    return fab(n-1) + fab(n-2);
}

TEST(FutureTest, async)
{
    print_thread_id();
    future<int> f1 = async(launch::async,fab, 5);
    future<int> f2 = async(launch::deferred, fab, 7);
    int ret1 = f1.get();
    cout << "f1=" << ret1 << endl;
    assert(ret1 == 8);
    int ret2 = f2.get();
    cout << "ret2=" << ret2 << endl;
    assert(ret2 == 21);

}