#include "run_example.h"
#include <cmath>

using namespace std;


int lambda_demo(int argc, char* argv[])
{
    auto print = [](const int& n) { BOOST_LOG_TRIVIAL(trace) << "number: " << n; };
    vector<int> v = {1, 2, 3,4, 5};
    for_each(v.begin(), v.end(), print);
    
    auto num = 1;
    auto add = [num](int n) { return num + n; };
    BOOST_LOG_TRIVIAL(trace) << "added number: " << add(10);


    double pi = 3.14;
    auto cal_area = [pi](double r) {return pi * pow(r, 2.0); };
    BOOST_LOG_TRIVIAL(trace) << "area: " << cal_area(10);
    
    return 0;
}
