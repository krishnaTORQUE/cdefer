#include "system_stream.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void system_stream(char* command) {
    FILE* f;
    char buffer[256];

#ifdef _WIN32
    f = _popen(command, "r");
#else
    f = popen(command, "r");
#endif

    if (!f) {
        printf("[ERROR] Command popen fail.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), f)) {
        printf("%s", buffer);
        fflush(stdout);
    }

#ifdef _WIN32
    int r = _pclose(pipe);
#else
    int r = pclose(f);
#endif

    if (r != 0) {
        printf("[ERROR] Command '%s' failed with exit code %d.\n", command,
               WEXITSTATUS(r));
    }
}
