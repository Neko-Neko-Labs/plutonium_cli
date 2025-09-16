#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include "pluginSdk.h"

void run(Args *ar)
{
    void *handle;
    int (*plugin_entry)(Args *);
    char *error;

    char buf[512] = "";
    snprintf(buf, sizeof(buf), "./plugins/%s/%s.so", ar->plug, ar->plug);
    handle = dlopen(buf, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    dlerror(); // clear

    *(void **)(&plugin_entry) = dlsym(handle, ar->func);
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    // Call plugin with struct
    plugin_entry(ar);

    dlclose(handle);
}

void runCore(Args *ar, char *func)
{
    ar->plug = "core";
    ar->func = func;
    run(ar);
    freeArgs(ar);
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <command> <arg>\n", argv[0]);
        return 1;
    }

    char *p = argv[1];

    while (*p) {
        switch (*p) {
            case 'l': {
                Args *ar = malloc(sizeof(Args));
                ar->argsLen = 1;
                ar->args = malloc(sizeof(void*) * ar->argsLen);
                ar->args[0] = argv[2];   // pass string
                ar->order = "s";         // describe type order
                runCore(ar, "plcliLs");
                break;
            }
        }
        p++;
    }
    return 0;
}

