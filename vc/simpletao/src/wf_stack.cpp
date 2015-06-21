#include "common.h"
#include "wf_stack.h"

STACK * create_stack(uint32_t uStackSize) {
	STACK * pStack;
	if(uStackSize == 0) {
		return NULL;
	}

	pStack = (STACK *) malloc(sizeof(struct STACK_st));

	if(pStack != NULL) {
		pStack->ppBase = (void **)malloc(uStackSize * sizeof(void*));

		if(pStack->ppBase == NULL) {
			free(pStack);
			pStack = NULL;
		} else {
			pStack->ppBase[0] = NULL;
			pStack->uTop = 0;
			pStack->uStackSize = uStackSize;
		}
	}

	return pStack;

}


void destory_stack(STACK *pStack, DESTROYFUNC destroyFunc) {
    if ( pStack != NULL )
    {
        if ( pStack->ppBase != NULL )
	    {
			if ( destroyFunc != NULL )
			{
				UINT i;
				for ( i = 0; i < pStack->uTop; i++ )
				{
					if ( pStack->ppBase[i] != NULL )
					{
						(*destroyFunc)(pStack->ppBase[i]);
					}
				}
			}
			free( pStack->ppBase );
        }
        free( pStack );
        pStack = NULL;
    }
}


void * pop_stack( STACK * pStack )
{
	void	*pData;

	if ( pStack == NULL || pStack->uTop == 0 )
	{
		return NULL;
	}

	pStack->uTop -= 1;

	pData = pStack->ppBase[pStack->uTop];
	
	return pData;
}

int push_stack( STACK * pStack, void *pData )
{
	if ( pStack == NULL )
	{
		return RET_FAILED;
	}


	if ( pStack->uTop >= pStack->uStackSize - 1 )
	{
		pStack->ppBase = (void **)realloc( pStack->ppBase, 
            ( pStack->uStackSize * 2 ) * sizeof( void * ) );
		if ( pStack->ppBase == NULL )
		{
			return RET_FAILED;
		}
		pStack->uStackSize *= 2;
	}
	pStack->ppBase[pStack->uTop] = pData;
	pStack->uTop += 1;

	return RET_SUCCESS;
}