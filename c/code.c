#include <stdio.h>
#include <stdlib.h>

int accum = 0;

int sum(int x, int y)
{
    int t = x + y;
    accum += t;
    return t;
}

int main(int argc, char* argv[])
{
	accum = 12;
	
	printf("--- byebye ---");
	return 0;
}
