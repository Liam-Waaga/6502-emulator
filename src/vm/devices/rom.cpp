
#include "vm/devices/rom.hpp"
#include "log/log.h"
#include "common/common.hpp"
#include "vm/devices/device.hpp"

#include <sys/mman.h>
#include <fcntl.h>
#include <filesystem>


ROM::ROM(Word begin_address, Word end_address, unsigned offset, std::filesystem::path file) {
    /* file length */
    unsigned long file_length = 0;

    /* if the file doesn't exist, error */
    if (!std::filesystem::exists(file)) {
        this->_error |= FILE_NOT_EXIST;
        logf(ERROR, "File \"%s\" does not exist but used for ROM source", file.c_str());
        std::exit(1);
    }

    /* get file size */
    file_length = std::filesystem::file_size(file);
    this->_filemap_length = file_length;

    /* set the addresses*/
    set_addresses(begin_address, end_address);

    /* open the file */
    this->_file_fd = open(file.c_str(), O_RDONLY);
    if (this->_file_fd == -1) {
        logf(ERROR, "File \"%s\" exists but could not be opened", file.c_str());
        std::exit(1);
    }

    /* finally mmap the file */
    /* don't use offset because it probably isn't a multiple of page, and we want to support arbitrary offsets*/
    this->_filemap = (Byte *) mmap(nullptr, file_length, PROT_READ, MAP_PRIVATE, this->_file_fd, 0);

    /* offset checking */
    if (offset + end_address >= file_length) {
        logf(WARN, "Offset (%d) for file \"%s\" (%d bytes) may overflow, setting to 0", offset, file.c_str(), file_length);
        offset = 0;
    }
    logf(INFO, "Registered offset %d for \"%s\"", offset, file.c_str());
    this->_offset = offset;
    if (offset + end_address >= file_length) {
        logf(ERROR, "End address (%d) for file \"%s\" (%d bytes) may overflow, unable to continue", end_address, file.c_str(), file_length);
        std::exit(1);
    }

    if (this->_filemap == (Byte *) -1) {
        this->_error |= MMAP_FAILED;
        logf(ERROR, "Failed to mmap \"%s\" at fd %d with length %d", file.c_str(), this->_file_fd, file_length);
        std::exit(1);
    }
}

ROM::~ROM() {
    munmap(_filemap, this->_filemap_length);
}
