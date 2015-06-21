#include "gmock/gmock.h"
#include <string>
#include <iostream>

void foo(short* pModuleID)
{
	printf("foo:: nModuleID = %d\n", *pModuleID);
}

TEST(BasicConceptTest, EndianTest)
{
	int nModuleID = 3;
	foo((short*)&nModuleID);
	printf("main:: nModuleID = %d\n", nModuleID);
}