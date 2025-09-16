#include "headers/plclils.h"
#include "headers/utils.h"
#include "headers/pluginSdk.h"
#include <stdio.h>
#include <string.h>

#ifdef __linux__
#include <dirent.h>
#define OPENDIR opendir 
#define READDIR readdir 
#define CLOSEDIR closedir 
#endif

int plcliLs(Args *args)
{
    if (strcmp(args->order, "s") != 0) {
        errf("Wrong arg order! Excepted [s], Got [%s].", args->order);
        return -1;
    }

    char *path = args->args[0]; 

    if (!path) {
        errf("No path given");
        return -1;
    }

    DIR *dir;
    struct dirent *entry;

    dir = OPENDIR(path);
    if (!dir) {
        errf("Can't open the directory: %s", path);
        return -1;
    }

    while ((entry = READDIR(dir)) != NULL)
        printf("%s\n", entry->d_name);

    CLOSEDIR(dir);
    return 0;
}
