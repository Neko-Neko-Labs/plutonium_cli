#include "headers/utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers/colors.h"

#ifdef __linux__
#include <dirent.h>
#include <sys/stat.h>
#define OPENDIR opendir
#define CLOSEDIR closedir
#define READDIR readdir
#else
errf("Un Supported OS");
#endif

typedef struct dirent Dirent;

typedef struct File {
    char* name;
    enum {
        KFILE,
        KDIR,
        CODE,
        LINK,
    } type;
} File;

/*
 * Takes the element, array and size of it.
 * moves in array till it founds it.
 * if found retunrs 1;
 * if not return 0;
 * Unix-like returning like 0 pass, 1 fail. like int main;
 * ----DOC INFO----
 *  By: Koofte
 *  Level: 4 Byte
 */
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

File getElement(Dirent *entry)
{

    char *ext = get_extension(entry->d_name);
    char *codeFiles[] = {"c", "py", "cpp", "java", "h", "hpp", "js"};
    int isCode = ext ? includes(codeFiles, sizeof(codeFiles)/sizeof(codeFiles[0]), ext) : 0;
    File flTemp = {
        .name = entry->d_name,
        .type = KFILE
    };
    if (isCode) {
        flTemp.type = CODE;
    } else {
        switch (entry->d_type) {
            case DT_DIR:
                flTemp.type = KDIR;
                break;
            case DT_LNK:
                flTemp.type = LINK;
                break;
        }
    }
    return flTemp;
}

int plcliLs(char *path, int showAll, int bbatch) 
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
    int i = 0;
    int bcSize = bbatch;
    File batch[bcSize];
    while ((entry = READDIR(dir)) != NULL) {
        int hidden = entry->d_name[0] == '.' ? 1 : 0;
        if (hidden && !showAll) {
            continue;
        }

        File temp = getElement(entry);
        batch[i++] = temp;
        if (i == bcSize) {
            for (int i = 0; i < bcSize; ++i) {
                if (batch[i].type == KDIR) printf("%s%s%s\t", C_CYAN, batch[i].name, STYLE_RESET);
            }
            for (int i = 0; i < bcSize; ++i) {
                if (batch[i].type != KDIR) {
                    char *typ;
                    switch (batch[i].type) {
                        case KFILE: typ=C_GREEN; break;
                        case LINK: typ=C_BLACK; break;
                        case CODE: typ=C_YELLOW; break;
                    }
                    printf("%s%s%s\t", typ, batch[i].name, STYLE_RESET);
                }
            }
            i=0;
            printf("\n"); //new line;
        }
    }
    for (int j = 0; j < i; ++j) {
        if (batch[j].type == KDIR) printf("%s%s%s\t", C_CYAN, batch[j].name, STYLE_RESET);
    }
    for (int j = 0; j < i; ++j) {
        if (batch[j].type != KDIR) {
            char *typ;
            switch (batch[j].type) {
                case KFILE: typ=C_GREEN; break;
                case LINK: typ=C_BLACK; break;
                case CODE: typ=C_YELLOW; break;
            }
            printf("%s%s%s\t", typ, batch[j].name, STYLE_RESET);
        }
    }
    printf("\n");
    CLOSEDIR(dir);
    return 0;
}

