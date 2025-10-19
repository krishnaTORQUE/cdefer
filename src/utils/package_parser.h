#ifndef PACKAGE_PARSER_H
#define PACKAGE_PARSER_H

#include <stdio.h>

typedef void (*package_parser_cb)(char* section, char* key, char* value);

void package_parser(FILE* f, package_parser_cb cb);

#endif
