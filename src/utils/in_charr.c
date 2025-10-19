#include "in_charr.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

int16_t in_charr(char* s, char a[][1024]) {
    int16_t x = -1;

    for (uint16_t i = 0; i < sizeof(a[0]); i++) {
        if (strlen(s) > 0 && strlen(a[i]) > 0 && strstr(s, a[i])) {
            x = i;
            break;
        }
    }

    return x;
}
