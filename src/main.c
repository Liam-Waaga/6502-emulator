
#include "types.h"
#include "log/log.h"
#include "mem.h"



RUNTIME_FLAGS flags;

int main(int argc, char **argv, char **envv) {
    flags.ram_size = 0x8000;
    flags.rom_size = 0x8000;
    flags.loglevel = 0;
    log_error("test %s", "other_test");
    return 0;
}