#ifndef _WF_DEFINE_H
#define _WF_DEFINE_H

#include <stdint.h>

typedef void (*DESTROYFUNC) ( void *pData );


typedef struct STACK_st {
	void ** ppBase;    // the array that record data
	uint32_t uTop;       // stack top location
	uint32_t uStackSize; // stack size
} STACK;


STACK * create_stack(uint32_t uStackSize);

void destory_stack(STACK* pStack, DESTROYFUNC destoryFunc);

void * pop_stack(STACK * pStack);

int push_stack(STACK * pStack, void * pData);

#endif