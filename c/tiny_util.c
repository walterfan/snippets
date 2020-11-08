#include <stdio.h>

int round_to_int(float number) {
    return (int)(number + 0.5);
}


int text_to_wav(char* text, char* wave) {
    printf("convert '%s' to wave file '%s'\n", text, wave);
    return 0;
}