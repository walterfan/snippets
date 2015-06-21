//from http://stackoverflow.com/questions/6478895/efficient-way-to-translate-a-char-to-an-enum-value
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#if defined(_WIN32) || defined(_WIN64)
/* We are on Windows */
# define strtok_r strtok_s
#endif

#define CREATEENUM(name, first, ...) \
    typedef enum { first = 0, __VA_ARGS__ } name; \
    char name##_s[] = #first ", " #__VA_ARGS__;
#define TOSTR(x) #x
#define TOENUM(name, x) ((name) _toenum(name##_s, x))

long _toenum(char *enum_s, const char *x) {
    long i = 0;
    size_t len = strlen(enum_s);

    char *copy = (char*) malloc(sizeof(char) * (len + 1));
    strncpy(copy, enum_s, len);
    copy[len] = '\0';

    char *saveptr = NULL;
    char *s = strtok_r(copy, ", ", &saveptr);
    do {
        if (strcmp(s, x) == 0) {
            free(copy);
            return i;
        }
        i++;
    } while((s = strtok_r(NULL, ", ", &saveptr)) != NULL);

    free(copy);
    return -1;
}

/*** END HACK ***/

// create enum with the name "super"
CREATEENUM(kEventType,
    REQUEST,
    RESPONSE,
    NOTIFICATION
)

int main(int argc, char *argv[]) {
    printf("%d\n", TOENUM(kEventType, "REQUEST")); // 3
    printf("%d\n", TOENUM(kEventType, "RESPONSE")); // -1 (not found)
    printf("%d\n", TOENUM(kEventType, "NOTIFICATION")); // 0

    printf("%s\n", TOSTR(NOTIFICATION)); // AWESOME
    return 0;
}
