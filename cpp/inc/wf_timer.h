/*
* Copyright  2005 JinWei Bird Studio All rights reserved
*
* Filename: wf_timer.h
* Description: timer header file
*
* Version:1.0
* Create date: 08/19/2005
* Author: Walter Fan, walter.fan@gmail.com
*/

#ifndef __WF_TIMER_H__
#define __WF_TIMER_H__
#include <iostream>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <chrono>

using namespace std;
using namespace std::chrono;


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

#endif