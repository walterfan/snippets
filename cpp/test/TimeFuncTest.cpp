#include "gmock/gmock.h"
#include "StringUtil.h"
#include "wf_timer.h"
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


TEST(TimeUtilTest, getCurrentTime) {

    uint32_t duration1 = getCurrentTime();
    usleep(1000000 + 2367);

    uint32_t duration2 = getCurrentTime();
    cout<< "duration1=" << duration1 << ", duration2=" << duration2 <<endl;
}