
#include "types.h"
#include "mem.h"



struct RUNTIME_FLAGS flags;

int main(void) {
    flags.ram_size = 0x8000;
    flags.rom_size = 0x8000;
    ADDR_SPACE *address_space = addr_init(flags);

    return 0;
}