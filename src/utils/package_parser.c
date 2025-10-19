#include "package_parser.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "trim.h"

void package_parser(FILE* f, package_parser_cb cb) {
    char line[1024] = "";
    char section[64] = "";

    while (fgets(line, sizeof(line), f)) {
        trim(line);

        if (line[0] == '\0' || line[0] == '#' || line[0] == ';') continue;

        if (line[0] == '[') {
            char* end = strchr(line, ']');

            if (end) {
                *end = '\0';
                snprintf(section, sizeof(section), "%s", line + 1);
            }
        } else {
            char* eq = strchr(line, '=');

            if (eq) {
                *eq = '\0';
                char key[128], value[1024];

                snprintf(key, sizeof(key), "%s", line);
                snprintf(value, sizeof(value), "%s", eq + 1);

                trim(key);
                trim(value);
                cb(section, key, value);
            } else {
                char value[1024];
                snprintf(value, sizeof(value), "%s", line);

                trim(value);
                cb(section, NULL, value);
            }
        }
    }
}
