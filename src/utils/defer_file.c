#include "defer_file.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "replacer.h"
#include "trim.h"

void defer_file(FILE* f, char* code_cb) {
    uint16_t depth = 0;
    uint16_t defers_i = 0;
    char line[1024] = "";
    char defers[1024][1024] = {};
    char code[1024 * 1024] = "";

    while (fgets(line, sizeof(line), f)) {
        /**
         * Reset depth
         */
        if (depth == 0) {
            memset(defers, 0, sizeof(defers));
            defers_i = 0;
        }
        /**
         * Check depth
         */
        if (strchr(line, '{')) {
            depth += 1;
        } else if (strchr(line, '}')) {
            depth -= 1;
        }
        /**
         * Allocate & free memory
         */
        if (strstr(line, "#include") && strstr(line, "defer.h")) {
            continue;
        } else if (strstr(line, " Defer ")) {
            char* x = replacer(line, " Defer ", "");
            snprintf(defers[defers_i], sizeof(defers[defers_i]), "%s", x);
            defers_i += 1;
        } else if (strstr(line, " return ") && !strstr(line, " //")) {
            char* returned = replacer(line, "return ", "");
            returned = replacer(returned, ";", "");
            trim(returned);

            char d[1024] = "";
            uint16_t d_i = 0;
            for (uint16_t i = 0; i < defers_i; i++) {
                if (!strstr(defers[i], returned)) {
                    char* x = defers[i];
                    trim(x);
                    d_i += snprintf(d + d_i, sizeof(d) - d_i, "%s", x);
                }
            }

            snprintf(d + strlen(d), sizeof(d) - strlen(d), " return ");
            char* x = replacer(line, " return ", d);
            snprintf(code + strlen(code), sizeof(code) - strlen(code), "%s", x);
        } else {
            snprintf(code + strlen(code), sizeof(code) - strlen(code), "%s",
                     line);
        }
    }

    snprintf(code_cb, sizeof(code), "%s", code);
}
