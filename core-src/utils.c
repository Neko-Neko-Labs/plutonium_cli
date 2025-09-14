#include "headers/utils.h"
#include <stdarg.h>
#include <stdio.h>

void errf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    fprintf(stderr, "[ERROR]: { %s:%d - %s %s } ", __FILE__, __LINE__, __TIME__, __DATE__);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
}

