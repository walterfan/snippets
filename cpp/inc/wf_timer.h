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

#include <chrono>
using namespace std::chrono;

class TimerBase {
public:
    TimerBase():m_start(system_clock::time_point::min()) {

    }

    void Clear() {
        m_start = system_clock::timer_point::min();
    }

    bool IsStarted() const {
        return m_start.time_since_epoch() != system_clock::duration(0);
    }

    void Start() {
        m_start = system_clock::now();
    }

    unsigned long GetMS() {
        if(IsStarted()) {
            system_clock::duration diff;
            diff = system_clock::now() - m_start;
            return (unsigned)(duration_cast<milliseconds>(diff).count());
        }
        return 0;
    }
private:
    system_clock::time_point m_start;
};

template <typename T> class basic_stopwatch: T {
    typedef typename T BaseTimer;
public:
    explict basic_stopwatch(bool start);
    explict basic_stopwatch(char const* activity = "Stopwatch", bool start = true);    
};

#endif