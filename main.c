#include "headers/utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers/plclils.h"

/**
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
 **/

typedef struct LsSettings {
    int showall, humanreadable, showsize, batch;
} LsSettings;

LsSettings readLsOption(char *opt)
{
    if (opt[0] != '-') { errf("Unable to read 'ls'(List) settings. Pls try again"); exit(1); }
    LsSettings set = {
        .humanreadable = 0,
        .showsize = 0,
        .showall = 0,
        .batch=5
    };
    char *p = opt;
    while (*p) {
        switch (*p) {
            case 'a':
                set.showall = 1;
                break;
            case 'h':
                set.humanreadable = 1;
                break;
            case 's':
                set.showsize = 1;
                break;
            case 'l': 
                ++p;
                if (isdigit(*p)) {
                    set.batch = atoi(p);
                    while (isdigit(*p)) ++p;
                    continue;
                }
                break;
        }
        ++p; //again feels optimized then p++;
    }
    return set;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        errf("Wrong usage plcli <action> [options]");
        return 1;
    }

    char *p = argv[1];

    while (*p) {
        switch (*p) {
            case 'l': 
                printf("");
                LsSettings set;
                int opindex = 2;
                if (argc < 3) argv[2] = ".";
                if (argc < 4) {
                    set.showall = 0;
                    set.humanreadable = 0;
                    set.showsize = 0;
                    opindex = 3; //so it uses argv[2]... dont mind it. it works
                } else {
                    opindex = 2;
                    if (argv[2][0] != '-' && argv[3][0] == '-') opindex=3;
                    set = readLsOption(argv[opindex]);
                }
                plcliLs(opindex == 3 ? argv[2] : argv[3], set.showall, set.batch);
                break;
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

