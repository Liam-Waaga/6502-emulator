/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/da-ostrich-king/6502-emulator/blob/main/LICENSE.md
 */


#include "cpu.h"
#include "instruction.h"
#include "parcer.h"
#include "types.h"
#include "log/log.h"
#include "mem.h"
#include "parcer.h"

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
    printf("Usage: %s\n", argv0);
    printf("       %s <file>\n", argv0);
    printf("       ./<file> # with shebang\n");
    printf("\n");
    printf("Arguments:\n");
    printf("    --help  -h    Show this message\n");
    printf("    --license     Display license details\n");
    exit(0);
}

static const struct option cmd_options[] = {
    {"help",    optional_argument, NULL, 'h'},
    {"license", optional_argument, NULL, 'l'},
    {0, 0, 0, 0}
};

int main(int argc, char **argv) {
    printf("%s", LICENSE_MESSAGE);
        
    char *memconfig_file = DEF_MEMCONFIG_FILE_PATH;
    
    int opt;
    while ((opt = getopt_long(argc, argv, "h", cmd_options, NULL)) != -1) {
        switch (opt) {
            case 'h': {
                usage(argv[0]);
            }
            case 'l': {
                printf("%s\n\n", FULL_LICENSE);
                printf(
                    "END OF LICENSE TEXT\n"
                    "Hello, I recommend you view this license text with a terminal pager (ex, appending ' | less' to the command)\n"
                    "or to view the license on github at %s/main/LICENSE.md\n",
                    GIT_LINK
                );
                exit(0);
            }
        }
    }

    PARCER_DEVICE *parcer_arr = parce_file(memconfig_file);
    // print_parcer_dev_arr(parcer_arr);

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
