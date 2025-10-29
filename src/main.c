#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/defer_task.h"
#include "utils/list_dir.h"
#include "utils/makefile.h"
#include "utils/package_parser.h"
#include "utils/system_stream.h"

#define NAME "cdefer"
#define VERSION "0.3.0"

/**
 * Mod Object
 */
struct ModObj {
    char key[64];
    char value[1024];
};
/**
 * Package details
 */
uint16_t compiler_flags_i = 0;
uint16_t mod_i = 0;
uint32_t linkers_i = 0;
char compiler[16] = "";
char compiler_flags[1024][1024] = {};
struct ModObj mod[128];
char linkers[1024][1024] = {};
/**
 * Get package details
 */
void package_file_cb(char* section, char* key, char* value) {
    /**
     * Compiler
     */
    if (strcmp(section, "package") == 0 && strcmp(key, "compiler") == 0) {
        snprintf(compiler, sizeof(compiler), "%s", value);
    }
    /**
     * Compiler flags
     */
    if (strcmp(section, "compiler_flags") == 0) {
        char x[1024] = "";

        if (key) {
            snprintf(x, sizeof(x), "%s=%s", key, value);
        } else {
            snprintf(x, sizeof(x), "%s", value);
        }

        snprintf(compiler_flags[compiler_flags_i],
                 sizeof(compiler_flags[compiler_flags_i]), "%s", x);

        compiler_flags_i += 1;
    }
    /**
     * Mod
     */
    if (strcmp(section, "mods") == 0) {
        snprintf(mod[mod_i].key, sizeof(mod[mod_i].key), "%s", key);
        snprintf(mod[mod_i].value, sizeof(mod[mod_i].value), "%s", value);
        mod_i += 1;
    }
    /**
     * Linkers
     */
    if (strcmp(section, "linkers") == 0) {
        snprintf(linkers[linkers_i], sizeof(linkers[linkers_i]), "%s", value);
        linkers_i += 1;
    }
}

int main(int argc, char* argv[]) {
    char command[128] = "";

    for (uint16_t i = 1; i < argc; i++) {
        /**
         * Version
         */
        if (strcmp(argv[i], "version") == 0) {
            printf("%s v%s\n", NAME, VERSION);
            exit(0);
        } else {
            /**
             * Rest of the command
             */
            snprintf(command, sizeof(command), "%s", argv[i]);
        }
    }

    printf("[INFO] Preparing\n");
    /**
     * Open file
     */
    FILE* file_ptr = fopen("cdefer.ini", "r");
    if (!file_ptr) {
        printf("[ERROR] cdefer.ini file not found\n");
        return 1;
    }

    printf("[INFO] Getting package details\n");

    package_parser(file_ptr, package_file_cb);
    fclose(file_ptr);

    printf("[INFO] Cleaning\n");
    /**
     * Directories
     */
    system_stream("rm -rf build");
    system_stream("mkdir -p build/out");
    system_stream("cp -r src build");
    /**
     * Preprocessing
     */
    printf("[INFO] Preprocessing files\n");

    char list_dir_file[1024][1024] = {};
    uint16_t list_dir_file_i = 0;
    list_dir("build/src", list_dir_file, &list_dir_file_i);

    for (uint16_t i = 0; i < list_dir_file_i; i++) {
        if (strlen(list_dir_file[i]) < 1) break;
        defer_task(list_dir_file[i]);
    }
    /**
     * Makefile
     */
    printf("[INFO] Creating makefile\n");

    char code[1024 * 1024];
    makefile(compiler, compiler_flags, linkers, code);

    FILE* makefile_ptr = fopen("build/makefile", "w");
    if (!makefile_ptr) {
        printf("[ERROR] Fail to create makefile\n");
        return 1;
    }

    fprintf(makefile_ptr, "%s", code);
    fclose(makefile_ptr);
    /**
     * Make
     */
    system_stream("cd build && make build");
    /**
     * Run
     */
    if (strcmp(command, "run") == 0) system_stream("build/main");

    return 0;
}
