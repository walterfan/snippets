/*
 * stl_benchmark.cpp
 *
 *  Created on: 2013-9-5
 *      Author: walter
 */

#include <vector>
#include <iostream>
#include <time.h>
#include <set>
#include <algorithm>
#include "google/profiler.h"

const int N = 3001;
using namespace std;

extern bool some_test;

set<int> get_set(int)
{
    set<int> s;
    for (int i = 0; i < N; ++i)
        while (!s.insert(rand()).second)
            ;
    if (some_test)
        return s;
    return set<int>();
}

vector<set<int> > generate()
{
    vector<set<int> > v;
    for (int i = 0; i < N; ++i)
        v.push_back(get_set(i));
    if (some_test)
        return v;
    return vector<set<int> >();
}

float time_it()
{
    clock_t t1, t2, t3, t4;
    clock_t t0 = clock();
    {
    vector<set<int> > v = generate();
    t1 = clock();
    cout << "construction took " << (float)((t1 - t0)/(double)CLOCKS_PER_SEC) << endl;
    sort(v.begin(), v.end());
    t2 = clock();
    cout << "sort took " << (float)((t2 - t1)/(double)CLOCKS_PER_SEC) << endl;
    rotate(v.begin(), v.begin() + v.size()/2, v.end());
    t3 = clock();
    cout << "rotate took " << (float)((t3 - t2)/(double)CLOCKS_PER_SEC) << endl;
    }
    t4 = clock();
    cout << "destruction took " << (float)((t4 - t3)/(double)CLOCKS_PER_SEC) << endl;
    cout << "done" << endl;
    return (float)((t4-t0)/(double)CLOCKS_PER_SEC);
}

int main()
{
    ProfilerStart("perf_profile");
    cout << "N = " << N << '\n';
    float t = time_it();
    cout << "Total time = " << t << '\n';
}

bool some_test = true;

