#include <stdio.h>
#include <stdlib.h>

#define DEBUG_TRACE printf

int main(int argc, char* argv[])
{
	DEBUG_TRACE("There are so many pearls in codes\n");
	if(argc == 1)
		getchar();
	return 0;
}
