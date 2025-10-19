#include "trim.h"

#include <ctype.h>
#include <string.h>

void trim(char* s) {
    char* start = s;
    char* end;

    while (isspace((unsigned char)*start)) start++;

    if (*start == 0) {
        *s = 0;
        return;
    }

    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';

    memmove(s, start, end - start + 2);
}
