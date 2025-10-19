#include "defer_task.h"

#include <stdio.h>
#include <stdlib.h>

#include "defer_file.h"
#include "in_charr.h"

void defer_task(char* path) {
    char code[1024 * 1024];

    FILE* f = fopen(path, "r");
    if (!f) {
        printf("[ERROR] Fail to open file: %s\n", path);
        return;
    }

    defer_file(f, code);
    fclose(f);
    /**
     * Unsafe keyword
     */
    char unsafe_keyword[1024][1024] = {" gets(",    " strcpy(",   " strcat(",
                                       " sprintf(", " vsprintf(", " atoi(",
                                       " atol(",    " atof(",     " strtok("};

    int16_t in_charr_i = in_charr(code, unsafe_keyword);

    if (in_charr_i >= 0) {
        printf("[ERROR] Unsafe keyword found: %s\n",
               unsafe_keyword[in_charr_i]);

        exit(0);
    }

    FILE* f2 = fopen(path, "w");
    if (!f2) {
        printf("[ERROR] Fail to write file: %s\n", path);
        return;
    }

    fprintf(f2, "%s", code);
    fclose(f2);
}
