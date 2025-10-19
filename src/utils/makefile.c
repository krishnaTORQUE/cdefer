#include "makefile.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "char_end.h"
#include "replacer.h"

void makefile(char* compiler, char compiler_flags[][1024], char linkers[][1024],
              char* code) {
    bool cpp = false;
    /**
     * Merge compiler flags
     */
    char compiler_flags_str[1024] = "";
    uint16_t compiler_flags_str_i = 0;

    for (uint16_t i = 0; i < sizeof(compiler_flags[0]); i++) {
        if (strlen(compiler_flags[i]) < 1) break;

        compiler_flags_str_i +=
            snprintf(compiler_flags_str + compiler_flags_str_i,
                     sizeof(compiler_flags_str) - compiler_flags_str_i, "%s ",
                     compiler_flags[i]);
    }
    /**
     * Merge linkers
     */
    char linkers_str[1024] = "";
    uint16_t linkers_str_i = 0;
    char linkers_out_str[1024] = "";
    uint16_t linkers_out_str_i = 0;

    for (uint16_t i = 0; i < sizeof(linkers[0]); i++) {
        if (strlen(linkers[i]) < 1) break;
        /**
         * Rename .c / .cpp to .o file
         */
        char* linker_o;
        if (char_end(linkers[i], ".cpp")) {
            if (!cpp) cpp = true;
            linker_o = replacer(linkers[i], ".cpp", ".o");
        } else if (char_end(linkers[i], ".c")) {
            linker_o = replacer(linkers[i], ".c", ".o");
        } else {
            continue;
        }
        /**
         * Get filename & extension
         */
        linker_o = strtok(linker_o, "/");
        char* linker_o_last = "";
        while (linker_o) {
            linker_o_last = linker_o;
            linker_o = strtok(NULL, "/");
        };
        /**
         * Linking
         */
        linkers_str_i += snprintf(
            linkers_str + linkers_str_i, sizeof(linkers_str) - linkers_str_i,
            "\t@$(CC) $(CFLAGS) -c %s -o out/%s\n", linkers[i], linker_o_last);
        /**
         * Building
         */
        linkers_out_str_i +=
            snprintf(linkers_out_str + linkers_out_str_i,
                     sizeof(linkers_out_str) - linkers_out_str_i, "out/%s ",
                     linker_o_last);
    }
    /**
     * Linking main file
     */
    if (cpp) {
        /**
         * Linking
         */
        snprintf(linkers_str + strlen(linkers_str),
                 sizeof(linkers_str) - strlen(linkers_str),
                 "\t@$(CC) $(CFLAGS) -c src/main.cpp -o out/main.o\n");
    } else {
        snprintf(linkers_str + strlen(linkers_str),
                 sizeof(linkers_str) - strlen(linkers_str),
                 "\t@$(CC) $(CFLAGS) -c src/main.c -o out/main.o\n");
    }
    /**
     * Makefile
     */
    char makefile_code[1024 * 1024] = "";

    snprintf(makefile_code, sizeof(makefile_code),
             "CC = %s\n"
             "CFLAGS = -I./src %s\n\n"
             "build:\n"
             "\t@echo [INFO] Building\n"
             "%s"
             "\t@echo [INFO] Linking\n"
             "\t@$(CC) $(CFLAGS) %s out/main.o -o main\n"
             "\t@echo [INFO] Change permission\n"
             "\t@chmod +x main\n"
             "\t@echo [INFO] Done\n\n"
             "clean:\n"
             "\t@echo [INFO] Cleaning\n"
             "\t@rm -rf src out\n",
             compiler, compiler_flags_str, linkers_str, linkers_out_str);

    snprintf(code, sizeof(makefile_code), "%s", makefile_code);
}
