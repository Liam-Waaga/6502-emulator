
#include "parcer.h"
#include "types.h"
#include "log/log.h"
#include "mem.h"
#include "parcer.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define DEF_MEMCONFIG_FILE_PATH "memconfig.conf"

RUNTIME_FLAGS flags;

_Noreturn void usage(char const * const argv0) {
    printf("Usage: %s\n", argv0);
    printf("       %s <file>\n", argv0);
    printf("       ./<file> # with shebang\n");
    printf("\n");
    printf("Arguments:\n");
    printf("    --help  -h    Show this message\n");
    exit(0);
}

int main(int argc, char **argv, char **envv) {
    // for (size_t i = 0; i < argc; i++)
    //     printf("%s\n", argv[i]);
        
    char *memconfig_file;
    if (argc == 1) {
        memconfig_file = DEF_MEMCONFIG_FILE_PATH;
    } else {
        for (size_t i = 1; i < argc; i++) {
            if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0) {
                usage(argv[0]);
            } else {
                memconfig_file = argv[i];
            }
        }
    }
    PARCER_DEVICE *parcer_arr = parce_file(memconfig_file);
    print_parcer_dev_arr(parcer_arr);
    return 0;
}