#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
using namespace std;

typedef uint8_t BYTE;
typedef uint8_t* BYTE_PTR;

void show_bytes(BYTE_PTR start, int len)
{
    int i;
    for (i = 0; i < len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((BYTE_PTR)&x, sizeof(int));
}

void show_float(float x) {

    show_bytes((BYTE_PTR)&x, sizeof(float));
}

void show_pointer(void* x) {
    show_bytes((BYTE_PTR)&x, sizeof(void *));
}


int show_bytes_test(int argc, char* argv[]) {
    int iX = 12345;
    cout<<"show_int "<<iX<<": ";
    show_int(iX);

    float fX = (float)iX;
    cout<<"show_float "<<fX<<": ";
    show_float(fX);

    int* pX = &iX;
    cout<<"show_pointer "<<pX<<": ";
    show_pointer(pX);

    const char* s = "12345";
    cout<<"show_bytes "<<s<<": ";
    show_bytes((BYTE_PTR)s, strlen(s));
    return 0;
}

