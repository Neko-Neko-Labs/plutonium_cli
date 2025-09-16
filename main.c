#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include "headers/pluginSdk.h"

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

    dlerror(); // clear previous errors

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
    freeArgs(ar); // assume this frees args + malloc'd stuff
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [options] [path]\n", argv[0]);
        return 1;
    }

    char *p = argv[1]; // first command, like "-l"

    while (*p) {
        switch (*p) {
            case 'l': { // list
                          Args *ar = malloc(sizeof(Args));
                          ar->argsLen = 2;
                          ar->args = malloc(sizeof(void*) * ar->argsLen);

                          int showAll = 0;    // default = off
                          char *path = ".";   // default = current dir

                          // parse remaining arguments
                          for (int i = 2; i < argc; i++) {
                              if (strcmp(argv[i], "-a") == 0) {
                                  showAll = 1;
                              } else if (argv[i][0] != '-') {
                                  path = argv[i];
                              }
                          }

                          // assign into Args
                          ar->args[0] = path;
                          ar->args[1] = malloc(sizeof(int));
                          *(int*)ar->args[1] = showAll;

                          ar->order = "si"; // string, int
                          runCore(ar, "plcliLs");
                          break;
                      }

            default:
                      if (*p != '-') {
                          fprintf(stderr, "Unknown command: -%c\n", *p);
                          return 1;
                      }
        }
        p++; // move to next char inside argv[1]
    }

    return 0;
}

