#include <stdio.h>

void swap(int *a, int *b) {

	int c = *a;
	*a = *b;
	*b = c;
}

int main(int argc, char** argv) {
	int a = 2;
	int b = 3;
	swap(&a, &b);
	printf("a=%d, b=%d\n", a,  b);
	return 0;
}
