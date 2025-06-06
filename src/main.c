
#include "types.h"
#include "log/log.h"
#include "mem.h"



RUNTIME_FLAGS flags;

int main(void) {
    flags.ram_size = 0x8000;
    flags.rom_size = 0x8000;
    flags.loglevel = 0;
    
    return 0;
}