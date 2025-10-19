#include "char_end.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool char_end(char* s, char* end) {
    size_t full_l = strlen(s);
    size_t end_l = strlen(end);

    if (end_l > full_l) return false;
    return strcmp(s + (full_l - end_l), end) == 0;
}
