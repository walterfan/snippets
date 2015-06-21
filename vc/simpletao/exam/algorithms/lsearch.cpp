#include <stdint.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include <string>
#include <iostream>

using namespace std;
using namespace testing;

int IntCmp(void* pLeft, void* pRight)
{
	int *p1 = (int *)pLeft;
	int *p2 = (int *)pRight;
	return *p1 - *p2;
}

int StrCmp(void* pLeft, void* pRight)
{
	char* s1 = *(char**)pLeft;
	char* s2 = *(char**)pRight;
	return strcmp(s1,s2);
}

void* lsearch(void* key, void* base, size_t nSize, size_t nElemSize
	, int(*CmpFn)(void*, void*))
{
	for(size_t i=0; i < nSize; ++i)
	{
		void* elemAddr = (char *)base + i* nElemSize;
		if(CmpFn(key, elemAddr) == 0)
		{
			return elemAddr;
		}
	}

	return NULL;
}

TEST(LsearchTest, SearchIntegerTest)
{
	int array[] = {4,2,3,7,11,6};
	size_t nSize = 6;
	int num = 7;
	void* pFound = lsearch((void*)&num, (void*)array, nSize, sizeof(int), IntCmp);
	if(pFound != NULL)
		cout<<"found " << *((int*)pFound)<<endl;

	ASSERT_TRUE(NULL != pFound);
}

TEST(LsearchTest, SearchStringTest)
{
	char* notes[] = {"Ab", "F#","B","Gb","D", "Eb"};
	size_t nSize = 6;
	char* str = "Eb";
	void* pFound = lsearch((void*)&str, (void*)&notes, nSize, sizeof(char*), StrCmp);
	if(pFound != NULL)
		cout<<"found "<< *((char**)pFound)<<endl;

	ASSERT_TRUE(NULL != pFound);
}