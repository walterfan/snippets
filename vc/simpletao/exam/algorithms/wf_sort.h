#ifndef _WF_SORT_H
#define _WF_SORT_H

#include <stdint.h>
#include "common.h"

template <typename T>
class SortUtils
{
public:
	static void insert_sort(T* pData, uint32_t len);
	static void insert_sort(vector<T>& vec);

	static void bubble_sort(T* pData, uint32_t len);
	static void select_sort(T* pData, uint32_t len);
	static void shell_sort(T* pData, uint32_t len);
	static void quick_sort(T* pData, uint32_t len);
	static void heap_sort(T* pData, uint32_t len);
	static void merge_sort(T* pData, uint32_t len);
};

template <typename T>
void SortUtils<T>::insert_sort(vector<T>& vec){
	int j = 0;
	int len = vec.size();
	for(int i = 1; i < len; ++i) {
		T tmp = vec[i];
		for(j = i; j >0 && tmp < a[j-1]; --j) {
			vec[j] = vec[j-1];
		}
		vec[j] = tmp;
	}
}

/*
insert into a sorted collection
such as sorting a[0] and a[1],
then insert a[2] into a[0] and a[1]
then insert a[n] into a[0] to a[n-1]
*/
template <typename T>
void SortUtils<T>::insert_sort(T* pData, uint32_t len)
{
    if(len < 2) return;

	for(uint32_t j=1;j<len;++j) {
		//the key to insert
		T key = *(pData+j);
		uint32_t i = j -1;
		while(i>=0 && *(pData+i) > key) {
			*(pData + i + 1) = *(pData + i);
			//printf("i=%d ", i);
			--i;
		}
	    *(pData+i+1) = key;
		printf("\nsorted result of round %d: ", j);
		for(uint32_t k=0;k<len;k++) {
			printf("%d ", *(pData + k));
		}
		printf("\n");
	
	}

	  
}

template <typename T>
void SortUtils<T>::merge_sort(T* pData, uint32_t len)
{
    if(len < 2) return;

	printf("TODO\n");

	  
}

#endif