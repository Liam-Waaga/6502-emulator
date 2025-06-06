
#include "types.h"
#include "mem.h"



struct RUNTIME_FLAGS flags;

int main(void) {
    flags.ram_size = 0x7FFF;
    ADDR_SPACE *address_space = addr_init(&flags);

    return 0;
}