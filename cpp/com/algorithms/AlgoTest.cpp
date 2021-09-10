#include <stdint.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include <string>
#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <boost/log/trivial.hpp>
#include <boost/timer/timer.hpp>

using namespace std;
using namespace testing;
using namespace boost::timer;

using ::testing::AtLeast;                    

#include "SortUtils.h"
#include "wf_timer.h"
#include "wf_fib.h"
#include "wf_ds.h"

typedef SingleLinkedList<string> StringList;
typedef SingleLinkedList<string>::Node StringListNode;

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
	const char* notes[] = {"Ab", "F#","B","Gb","D", "Eb"};
	size_t nSize = 6;
	const char* str = "Eb";
	void* pFound = lsearch((void*)&str, (void*)&notes, nSize, sizeof(char*), StrCmp);
	if(pFound != NULL)
		cout<<"found "<< *((char**)pFound)<<endl;

	ASSERT_TRUE(NULL != pFound);
}

TEST(SortUtilsTest, InsertSort)
{
	printf("--- insertion sort test---\n");
	int vals[6] = {5,2,4,6,1,3};
	for(int i=0;i<6;++i) {
		printf("%d ",vals[i]);
	}
	SortUtils<int>::insert_sort(vals,6);
	printf("\n--- insertion sort test result ---\n");
	for(int i=0;i<6;++i) {
		printf("%d ",vals[i]);
	}

}

TEST(FibTest, FibTest) {
	cpu_timer t1;
	int ret = fib(45);
	BOOST_LOG_TRIVIAL(trace) <<" 1. " << ret << " spent "<< t1.format();
	cpu_timer t2;
	ret = fib2(45);
	BOOST_LOG_TRIVIAL(trace) <<" 2. " << ret << " spent "<< t2.format(); 
}

TEST(ListNodeTest, CycleTest) {
	StringList aList;
	
	StringListNode* pNode  = new StringListNode("alice");
	aList.pushBack(pNode);
	StringListNode* pNode2  = new StringListNode("bob");
	aList.pushBack(pNode2);
	StringListNode* pNode3  = new StringListNode("carl");
	aList.pushBack(pNode3);

	StringListNode* pNode4  = new StringListNode("david");
	aList.pushBack(pNode4);

	StringListNode* pNode5  = new StringListNode("elain");
	aList.pushBack(pNode5);

	StringListNode* pNode6  = new StringListNode("frank");
	aList.pushBack(pNode6);
	pNode6->next = pNode3;

	const string hasCycle = aList.hasCycle()? "it has cycle": "it doesn't have cycle";

	cout << hasCycle << ", " << aList <<endl;
}

int main(int argc, char** argv) {
    printf("--- unit test ---\n");
    testing::GTEST_FLAG(output)="xml:unit_test_result.xml";
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
