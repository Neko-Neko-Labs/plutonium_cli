#ifndef PLCLI_PLUGIN_SDK
#define PLCLI_PLUGIN_SDK

#include <malloc.h>

typedef struct Args {
    size_t argsLen;
    void **args;
    char *plug, *func;
    char *order;
} Args;

void freeArgs(Args *args) {
    free(args->args);
    free(args);
}

#endif
