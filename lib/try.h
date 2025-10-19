#ifndef Try

#define Try(v, f, r) \
    do {             \
        v = f;       \
        if (!(v)) {  \
            r;       \
        }            \
    } while (0)

#endif
