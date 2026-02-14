
#include "vm/devices/rom.hpp"
#include "log/log.h"
#include "common/common.hpp"

#include <stdexcept>
#include <filesystem>

#include <sys/mman.h>
#include <fcntl.h>

#ifdef _WIN32
#error "Windows not supported, if this compiles I would be thoroughly surprised. Remove this #error statement in src/vm/devices/rom.cpp if you really want to try"
#endif


ROM::ROM(Word begin_address, Word end_address, unsigned offset, std::filesystem::path file) {
    /* file length */
    unsigned long file_length = 0;

    /* if the file doesn't exist, error */
    if (!std::filesystem::exists(file)) {
        throw std::runtime_error("Rom file not found");
    }

    /* get file size */
    file_length = std::filesystem::file_size(file);
    this->_filemap_length = file_length;

    /* set the addresses*/
    set_addresses(begin_address, end_address);

    /* open the file */
    this->_file_fd = open(file.c_str(), O_RDONLY);
    if (this->_file_fd == -1) {
        throw std::runtime_error("Rom file innaccessable");
    }

    /* finally mmap the file */
    /* don't use offset because it probably isn't a multiple of page, and we want to support arbitrary offsets */
    this->_filemap = (Byte *) mmap(nullptr, file_length, PROT_READ, MAP_PRIVATE, this->_file_fd, 0);

    /* offset checking */
    if (offset >= file_length) {
        throw std::out_of_range("Bad offset");
    }

    Logger::logf(Logger::INFO, "Registered offset %d for \"%s\"", offset, file.c_str());

    this->_offset = offset;

    if (offset + end_address >= file_length) {
        throw std::out_of_range("Bad end address");
    }

    if (this->_filemap == (Byte *) -1) {
        throw std::runtime_error("mmap failed");
    }
}

ROM::~ROM() {
    munmap(_filemap, this->_filemap_length);
}

void ROM::write_byte(Word address, Byte value) {
    /* supress -Wunused-paramater */
    (void) address;
    (void) value;

    Logger::log(Logger::INFO, "Attempting to write to ROM memory, which is in it's nature read-only, not writing. This is a bug in the 6502 program or its configuration.");

}