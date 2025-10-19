#ifndef MAKEFILE_H
#define MAKEFILE_H

#include <stdint.h>

void makefile(char* compiler, char compiler_flags[][1024], char linkers[][1024],
              char* code);

#endif
