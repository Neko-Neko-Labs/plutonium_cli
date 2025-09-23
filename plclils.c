#define _DEFAULT_SOURCE
#include "headers/utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers/colors.h"

#ifdef __linux__
#include <dirent.h>
#define OPENDIR opendir
#define CLOSEDIR closedir
#define READDIR readdir
#else
errf("Un Supported OS");
#endif

typedef struct dirent Dirent;

int includes(char **arr, int size, char *element)
{
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], element) == 0) {
            return 1; // true: found
        }
    }
    return 0; // false: not found
}

char *get_extension(const char *filename)
{
    if (!filename) return NULL;

    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) {
        return NULL;
    }

    return (char*)(dot + 1);
}

//Option one. Idk is slow or fast;
int getCount(char *path, int showAll)
{
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "ls %s -1 %s | wc -l", showAll ? "-a" : " ", path); //i like the fact ls -a -1 ~ and ls        -1 ~ same
    FILE *cd = popen(cmd, "r");

    if (!cd) {
        errf("Cant get the file count! We would mess up the listing order!");
        return -1;
    }

    char buf[128];
    int count;
    fgets(buf, sizeof(buf), cd);
    count = atoi(buf);

    if (count < 1) return -1;
    return count;
}

int getCount_but(char *path, int showAll)
{
    if (!path) { errf("No path given"); return -1; }
    DIR *dir = OPENDIR(path);
    if (!dir) { errf("Can't open the directory: %s", path); return -1; }
    int count = 0;
    Dirent *entry;
    while((entry = READDIR(dir)) != NULL) { 
        if (!showAll && entry->d_name[0] == '.') continue;
        ++count; //FEELS OPTIMIZED THEN count++ IDK IF ITS TRUE THOOOOO!!!! ALL CAPS BABY
    }
    return count;
}

int plcliLs(char *path, int showAll)
{
    if (!path) {
        errf("No path given");
        return -1;
    }

    DIR *dir = OPENDIR(path);
    if (!dir) {
        errf("Can't open the directory: %s", path);
        return -1;
    }

    Dirent *entry;
    while ((entry = READDIR(dir)) != NULL) {
        int hidden = entry->d_name[0] == '.' ? 1 : 0;
        if (hidden && !showAll) {
            continue; // skip hidden unless -a
        }

        char *ext = get_extension(entry->d_name);
        char *codeFiles[] = {"c", "py", "cpp", "java", "h", "hpp", "js"};
        int isCode = ext ? includes(codeFiles, sizeof(codeFiles)/sizeof(codeFiles[0]), ext) : 0;

        if (isCode) {
            printf("%s%s%s\n", hidden ? C_BRIGHT_RED : C_RED, entry->d_name, STYLE_RESET);
        } else {
            switch (entry->d_type) {
                case DT_DIR:
                    printf("%s%s%s\n", hidden ? C_BRIGHT_BLUE : C_BLUE, entry->d_name, STYLE_RESET);
                    break;

                case DT_REG:
                    printf("%s%s%s\n", hidden ? C_BRIGHT_WHITE : C_WHITE, entry->d_name, STYLE_RESET);
                    break;

                case DT_LNK:
                    printf("%s%s%s\n", hidden ? C_BRIGHT_CYAN : C_CYAN, entry->d_name, STYLE_RESET);
                    break;

                case DT_FIFO:
                    printf("%s%s%s\n", hidden ? C_BRIGHT_YELLOW : C_YELLOW, entry->d_name, STYLE_RESET);
                    break;

                case DT_SOCK:
                    printf("%s%s%s\n", hidden ? C_BRIGHT_MAGENTA : C_MAGENTA, entry->d_name, STYLE_RESET);
                    break;

                case DT_CHR:
                    printf("%s%s%s\n", hidden ? C_BRIGHT_RED : C_RED, entry->d_name, STYLE_RESET);
                    break;

                case DT_BLK:
                    printf("%s%s%s\n", hidden ? C_BRIGHT_GREEN : C_GREEN, entry->d_name, STYLE_RESET);
                    break;

                default:
                    printf("%s%s%s\n", hidden ? C_BRIGHT_BLACK : C_BLACK, entry->d_name, STYLE_RESET);
                    break;
            }
        }
    }

    CLOSEDIR(dir);
    return 0;
}

