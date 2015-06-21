#include "wf_sort.h"


void test_insert_sort()
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

