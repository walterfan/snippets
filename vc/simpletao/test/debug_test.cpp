#include <stdio.h>
#include <stdlib.h>
#include "gmock/gmock.h"

int factorial(int n)
{
    int result = 1;
    if(n ==0)
    {
        return result;
    }
    result = factorial(n-1)*n;
    return result;
}


TEST(DebugTest, factorial)
{
    int n = 10;
    int result = factorial(n);
    printf("factorinal %d = %d", n, result);
}
