#include "mem.h"
#include <stdlib.h>

ADDR_SPACE *addr_init(struct RUNTIME_FLAGS *run_flags) {
    ADDR_SPACE *addr_space = (ADDR_SPACE *) malloc(sizeof(*addr_space));
    addr_space->devices = malloc(sizeof(DEVICE) * 2);
    addr_space->dev_count = 2;
    // TODO, add to device array


    return addr_space;
}