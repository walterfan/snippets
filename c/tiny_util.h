#ifndef TINY_UTIL_H_
#define TINY_UTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

int round_to_int(float number);

int text_to_wav(char* text, char* wave);

#ifdef __cplusplus
}
#endif

#endif