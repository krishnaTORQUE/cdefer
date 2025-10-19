#include "replacer.h"

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char* replacer(char* s, char* from, char* to) {
    uint16_t count = 0;
    uint16_t old_l = strlen(from);
    uint16_t new_l = strlen(to);

    char* tmp = s;
    while ((tmp = strstr(tmp, from))) {
        count++;
        tmp += old_l;
    }

    uint16_t resultLen = strlen(s) + count * (new_l - old_l) + 1;
    char* result = malloc(resultLen);
    if (!result) return NULL;

    result[0] = '\0';

    char* current = s;
    while ((tmp = strstr(current, from))) {
        strncat(result, current, tmp - current);
        strcat(result, to);
        current = tmp + old_l;
    }

    strcat(result, current);
    return result;
}
