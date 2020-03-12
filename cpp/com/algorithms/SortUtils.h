#ifndef _WF_SORT_H
#define _WF_SORT_H

#include <stdint.h>
#include <vector>
using namespace std;

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
	static void merge_sort(vector<T>& vec);
};

template <typename T>
void SortUtils<T>::insert_sort(vector<T>& vec){
	int j = 0;
	int len = vec.size();
	for(int i = 1; i < len; ++i) {
		T selected = vec[i];
		for(j = i; j >0 && selected < a[j-1]; --j) {
			vec[j] = vec[j-1];
		}
		vec[j] = selected;
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
void merge_sort(vect<T>& vec, vector<T>& tempVec, int leftPos, int rightPos, int rightEnd) {
	int leftEnd = rightPos - 1;
	int tempPos = rightPos;
	int count = rightEnd - leftPos + 1

	while( leftPos <= leftEnd && rightPos <= rightEnd) {
		if(vec[leftPos] <= vec[rightPos]) {
			tempVec[tempPos++] = vec[leftPos++];
		} else {
			tempVec[tempPos++] = vec[rightPos++];
		}
	}
}


template <typename T>
void merge_sort(vect<T>& vec, vector<T>& tempVec, int left, int right) {
	if(left < right) {
		int center = (left + right)/2;
		merge_sort(a, tempVec, left, center);
		merge_sort(a, tempVec, center + 1, right);
		merge(vec, tempVec, left, center+1, right);
	}
}

template <typename T>
void SortUtils<T>::merge_sort(vector<T>& vec)
{
	vector<T> tempVec(vec.size());
	merge_sort(vec, tempVec, 0, vec.size()-1)

	printf("TODO\n");

	  
}


template <typename Comparable>
void shell_sort(vector<Comparable>& vec)
{
    int vec_size = vec.size();
    for(int gap = vec_size/2; gap > 0; gap = gap/2)
    {
   	    for(int i = gap; i < vec_size; i++) {
            Comparable selected = vec[i];
            int j = i;

            for(; j>=gap && selected < vec[j-gap]; j-=gap) {
            		vec[j] = vec[j-gap]
            }
            vec[j] = selected
        }
    }

}

#endif