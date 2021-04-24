#include "gmock/gmock.h"
#include "StringUtil.h"
#include <string>
#include <iostream>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

using namespace std;
using namespace testing;
using namespace wfan;
using ::testing::Return;
using ::testing::Mock;


uint32_t getCurrentTime() { // in ms
    static  struct timespec timeOffset = {0,0};
    struct timespec curTime;
    if (timeOffset.tv_sec ==0) {
      //CLOCK_MONOTONIC_COARSE is specified in linux  
      clock_gettime(CLOCK_MONOTONIC, &timeOffset);
      cout<<"static-only once, getCurrentTime() Init timeOffset sec=" << timeOffset.tv_sec << " nsec=" <<  timeOffset.tv_nsec <<endl;
    }
    clock_gettime(CLOCK_MONOTONIC, &curTime); // fast
    long ms = ((curTime.tv_nsec - timeOffset.tv_nsec))/1000000; 
    cout<<"getCurrentTime()  curTime sec=" << curTime.tv_sec << " nsec=" <<  curTime.tv_nsec << ", ms=" << ms <<endl;
    return ((curTime.tv_sec-timeOffset.tv_sec)*1000 + ms); 
  }

TEST(TimeUtilTest, getCurrentTime) {

    uint32_t duration1 = getCurrentTime();
    usleep(1000000 + 2367);

    uint32_t duration2 = getCurrentTime();
    cout<< "duration1=" << duration1 << ", duration2=" << duration2 <<endl;
}