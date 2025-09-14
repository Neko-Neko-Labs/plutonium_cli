#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <ini.h>
#include <string.h>
#include <stdarg.h>

void run(char *plugin, char *func, ...)
{
    va_list args;
    va_start(args, func);

    void *handle;
    int (*plugin_entry)(char *);
    char *error;

    char buf[512] = "";
    snprintf(buf, sizeof(buf), "./plugins/%s/%s.so", plugin, plugin);
    handle = dlopen(buf, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    dlerror();

    *(void **)(&plugin_entry) = dlsym(handle, func);
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    plugin_entry(va_arg(args, char*));
    va_end(args);
    dlclose(handle);
}

int main(int argc, char **argv)
{
    char *p = argv[1];

    while(*p) {
        switch (*p) {
            case 'l':
                run("core", "plcliLs", argv[2]);
                break;
        }
        p++;
    }
    return 0;
}

