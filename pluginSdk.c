#include "headers/pluginSdk.h"

void freeArgs(Args *args) {
    free(args->args);
    free(args);
}
