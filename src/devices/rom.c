#include "rom.h"
#include "../log/log.h"
#include <unistd.h>

ROM *rom_init(const char *path) {
    ROM *rom = (ROM *) malloc(sizeof(ROM));
    rom->fd = open(path, O_RDONLY);
    if (rom->fd == -1) {
        log_error("Failed to open ROM file descriptor at %s:%d", __FILE__, __LINE__);
        exit(1);
    }

    struct stat file_stat;

    if (fstat(rom->fd, &file_stat) == -1) {
        log_error("Failed to get ROM file status at %s:%d", __FILE__, __LINE__);
        close(rom->fd);
        rom->fd = -1;
        exit(1);
    }
    rom->size = file_stat.st_size;

    /* read into ram because we don't need to be reading from disc all the time */
    rom->data = (Byte_t *) malloc(rom->size);
    read(rom->fd, rom->data, rom->size);
    close(rom->fd);
    rom->fd = -1;

    log_info("Initialized ROM");
    return rom;
}

void rom_deinit(ROM *rom) {
    if (rom->fd != -1) close(rom->fd);
    free(rom->data);
    free(rom);
}
