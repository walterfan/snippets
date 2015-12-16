// DataCompression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// DataCompression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <string.h>
#include <math.h>
 
#define MAXLEN 100 //maximum string length
 
double log2( double n )  
{  
    // log(n)/log(2) is log2.  
    return log( n ) / log((double) 2 );  
}

int makehist(char *str,int *hist,int len){
	int wherechar[256];
	int i,histlen;
	histlen=0;
	for(i=0;i<256;i++)wherechar[i]=-1;
	for(i=0;i<len;i++){
		if(wherechar[(int)str[i]]==-1){
			wherechar[(int)str[i]]=histlen;
			histlen++;
		}
		hist[wherechar[(int)str[i]]]++;
	}
	return histlen;
}
 
double entropy(int *hist,int histlen,int len){
	int i;
	double H;
	H=0;
	for(i=0;i<histlen;i++){
		H-=(double)hist[i]/len*log2((double)hist[i]/len);
	}
	return H;
}
 
int _tmain(int argc, _TCHAR* argv[])
{
	char str[MAXLEN];
	int len,*hist,histlen;
	double H;
	printf("Please input a string:\n");
	scanf("%[^\n]",str);
	len=strlen(str);
	hist=(int*)calloc(len,sizeof(int));
	histlen=makehist(str,hist,len);
	//hist now has no order (known to the program) but that doesn't matter
	H=entropy(hist,histlen,len);
	printf("entropy: %lf\n",H);
	getchar();
	return 0;

}

