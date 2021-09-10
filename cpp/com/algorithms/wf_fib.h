#ifndef _WF_FIB_H
#define _WF_FIB_H

#include <vector>
using namespace std;

int fib(int n) {
    if(n == 0) return 0;
    if(n == 1 || n == 2) return 1;
    return fib(n-1) + fib(n-2);
}


int helper(vector<int>& memo, int n) {
    if(n == 1 || n == 2) return 1;
    if(memo[n] != 0) return memo[n];
    memo[n] = helper(memo, n-1) + helper(memo, n-2);
    return memo[n];
}

int fib2(int N) {
    if(N == 0) return 0;
    if(N == 1 || N == 2) return 1;
    vector<int> memo(N+1, 0);
    return helper(memo, N);
}
#endif