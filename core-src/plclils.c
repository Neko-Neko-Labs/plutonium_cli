int includes(char **arr, int size, char *element)
{
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], element) == 0) {
            return 1; // true: found
        }
    }
    return 0; // false: not found
}

int plcliLs(Args *args)
{
    if (strcmp(args->order, "si") != 0) {
        errf("Wrong arg order! Expected [si], got [%s].", args->order);
        return -1;
    }

    char *path = args->args[0];
    if (!path) {
        errf("No path given");
        return -1;
    }

    int showAll = *(int*)args->args[1];  // proper int flag

    DIR *dir = OPENDIR(path);
    if (!dir) {
        errf("Can't open the directory: %s", path);
        return -1;
    }

    struct dirent *entry;
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

