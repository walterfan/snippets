#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

struct st_node
{
	struct st_node * pNext;
	int nValue;
};


typedef void (*func_t)(int);

void foreach(struct st_node* pList, func_t func)
{
	while(pList){
		func(pList->nValue);
		pList =pList->pNext;

	}
}

void f(int n)
{
	printf("node(?)=%d\n", n);
}

TEST(functorTest, testcase1)
{
    cout<<"--- functorTest.testcase1 --"<<endl;
	
    struct st_node *pList = NULL;
    struct st_node *pNode = NULL;

    int i = 0;

    for(; i<4; i++)
    {
    	pNode = (struct st_node *)malloc(sizeof(struct st_node));
    	pNode->nValue = i;
    	pNode->pNext = pList;
    	pList = pNode;
    }

    i = 0;
    pNode = pList;
    while(pNode)
    {
    	printf("node(%d)=%d\n", i++, pNode->nValue);
    	pNode = pNode->pNext;

    }
    foreach(pList,f);
}
