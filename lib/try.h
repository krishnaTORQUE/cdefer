#ifndef Try

#include <stdio.h>

#define Try(v, f, r)                                    \
    do {                                                \
        printf("[WARN] Try macro has been deprecated"); \
        v = f;                                          \
        if (!(v)) {                                     \
            r;                                          \
        }                                               \
    } while (0)

#endif
