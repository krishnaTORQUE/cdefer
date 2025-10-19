#include "list_dir.h"

#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "char_end.h"

void list_dir(char* path, char file[][1024], uint16_t* file_i) {
    struct dirent* entry;
    DIR* dir = opendir(path);

    if (!dir) {
        printf("[ERROR] Fail to open directory: %s\n", path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        struct stat st;
        char fullpath[1024] = "";

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (stat(fullpath, &st) == -1) continue;

        if (S_ISDIR(st.st_mode)) {
            list_dir(fullpath, file, file_i);
        } else if (char_end(fullpath, ".cpp") || char_end(fullpath, ".c") ||
                   char_end(fullpath, ".h")) {
            snprintf(file[*file_i], sizeof(fullpath), "%s", fullpath);

            (*file_i) += 1;
        }
    }

    closedir(dir);
}
