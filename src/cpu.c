/* 
 * GNU GPLv3 License - see LICENSE.md at project root for terms.
 * If for any reason this file has been separated from the license text,
 * see LICENSE.md file in the git repo at https://github.com/da-ostrich-king/6502-emulator/blob/main/LICENSE.md
 */


#include "cpu.h"
#include "log/log.h"
#include "mem.h"
#include "clock.h"
#include "types.h"

#include <stdlib.h>

extern SYSTEM_FLAGS flags;


CPU *cpu_init(ADDR_SPACE *address_space) {
    log_info("Beginning CPU initialization");
    CPU *cpu = malloc(sizeof(CPU));
    if (cpu == NULL) {
        log_error("Allocation failure, %s:%d", __FILE__, __LINE__);
        exit(1);
    }
    cpu->address_space = address_space;
    cpu->PC = vm_read_word(address_space, 0xFFFC);

    log_info("Initializing CPU registers to default values");
    cpu->STAT = CPU_STAT_DEFAULT;
    cpu->Accumulator = 0;
    cpu->IndexRegX = 0;
    cpu->IndexRegY = 0;
    cpu->SP = 0x0100;

    log_info("Initializing clock");
    clock_init();
    return cpu;
}


void cpu_deinit(CPU *cpu) {
    log_info("Deinitializing CPU");
    log_info("Deinitializing address space");
    addr_deinit(cpu->address_space);
    log_info("Freeing CPU");
    free(cpu);
}
