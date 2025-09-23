#ifndef PLCLI_PLUGIN_SDK
#define PLCLI_PLUGIN_SDK

#include <malloc.h>

typedef struct Arg {
    enum {
        ARG_INT,
        ARG_CHAR,
        ARG_CHARP,
        ARG_FLOAT,
        ARG_VOIDP
    } type;
    union {
        int argi;
        char arhc;
        char *args; //string
        float argf;
        void *arhv;
    } val;
} Arg;

typedef struct Args {
    size_t argcount;
    Arg *args;
    char *plug, *func; 
} Args;

void freeArgs(Args *args);

#endif
