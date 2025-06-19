/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/Liam-Waaga/6502-emulator/blob/main/LICENSE.md
 */


#include "cpu.h"
#include "instruction.h"
#include "parcer.h"
#include "types.h"
#include "log/log.h"
#include "mem.h"
#include "parcer.h"

#include <bits/getopt_core.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#ifndef GIT_LINK
#error GIT_LINK not defined, define with -D... in build system.
#endif

#ifndef DEF_MEMCONFIG_FILE_PATH
#define DEF_MEMCONFIG_FILE_PATH "6502.conf"
#endif

SYSTEM_FLAGS flags;


const char *LICENSE_MESSAGE =
"    6502-emulator  Copyright (C) 2025  Liam Waaga\n"
"    This program comes with ABSOLUTELY NO WARRANTY\n"
"    This is free software, and you are welcome to redistribute it\n"
"    under certain conditions; run the program with the \"--license\" flag for details\n";


const char FULL_LICENSE[] = {
    #embed "../LICENSE.md"
    , 0
};

_Noreturn void usage(char const * const argv0) {
    printf(
        "Usage: %s\n"
        "       %s <file>\n"
        "\n"
        "Arguments:\n"
        "    -h  --help\n"
        "                    Show this message\n"
        "        --license\n"
        "                    Display license details\n"
        "        --loglevel [quiet,error,warn,info]\n"
        "                    Sets loglevel, overrides the loglevel in memconfig\n"
        "\n"
        , argv0, argv0
    );
    exit(0);
}

enum CMD_ARG_IDENT {
    ARG_HELP = 0,
    ARG_LICENSE,
    ARG_LOGLEVEL
};

static const struct option cmd_options[] = {
    {"help",       no_argument,       NULL, ARG_HELP},
    {"license",    no_argument,       NULL, ARG_LICENSE},
    {"loglevel",   required_argument, NULL, ARG_LOGLEVEL},
    {0, 0, 0, 0}
};

LOGLEVEL parce_loglevel(const char *arg) {
    if (strcmp(arg, "quiet") == 0) {
        return LOG_QUIET;
    } else if (strcmp(arg, "error") == 0) {
        return LOG_ERROR;
    } else if (strcmp(arg, "warn") == 0) {
        return LOG_WARN;
    } else if (strcmp(arg, "info") == 0) {
        return LOG_INFO;
    } else {
        log_error("Unknown log level: %s\n", arg);
        exit(1);
    }
}

int main(int argc, char **argv) {

    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    flags.loglevel = LOG_NONE;
        
    char *memconfig_file = malloc(strlen(DEF_MEMCONFIG_FILE_PATH) + 1);
    strncpy(memconfig_file, DEF_MEMCONFIG_FILE_PATH, strlen(DEF_MEMCONFIG_FILE_PATH) + 1);
    
    int opt;
    while ((opt = getopt_long(argc, argv, "h", cmd_options, NULL)) != -1) {
        switch (opt) {
            case ARG_HELP: {
                usage(argv[0]);
            }
            case ARG_LICENSE: {
                printf("%s\n\n", FULL_LICENSE);
                printf(
                    "END OF LICENSE TEXT\n"
                    "Hello, I recommend you view this license text with a terminal pager (ex, appending ' | less' to the command)\n"
                    "or to view the license on github at %s/main/LICENSE.md\n",
                    GIT_LINK
                );
                exit(0);
            }
            case ARG_LOGLEVEL: {
                flags.loglevel = parce_loglevel(optarg);
            }
        }
    }

    if (argc - optind > 0) {
        size_t len = strlen(argv[optind]) + 1;
        char *tmp = realloc(memconfig_file, len);
        if (!tmp) {
            log_error("Allocation failure at %s:%d", __FILE__, __LINE__);
            exit(1);
        }
        strncpy(tmp, argv[optind], len);
        memconfig_file = tmp;
    }
    
    PARCER_DEVICE *parcer_arr = parce_file(memconfig_file);
    print_parcer_dev_arr(parcer_arr);

    if (flags.loglevel > LOG_QUIET)
        printf("%s", LICENSE_MESSAGE);
    
    ADDR_SPACE *addr = addr_init(parcer_arr);
    CPU *cpu = cpu_init(addr);

    /* TODO, in the future, add an exit condition (make a ui, whether it is a tui, commandline, gui, etc, i haven't decided) */
    while (1) {
        execute_instruction(cpu, vm_read_byte(cpu->address_space, cpu->PC));
    }

    cpu_deinit(cpu);
    cpu = NULL;

    free_parcer_dev_arr(parcer_arr);
    return 0;
}
