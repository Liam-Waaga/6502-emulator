#pragma once

#include "vm/devices/device.hpp"
#include "common/common.hpp"

#include <cstddef>
#include <filesystem>

class ROM : Device {
    public:
    /* end_address + offset must be less than the file length */
    /* offset is offset from the beginning of the file, 0 means no offset*/
    ROM(Word begin_address, Word end_address, unsigned offset, std::filesystem::path file);
    ~ROM();
    
    Byte read_byte(Word address) const;
    
    void write_byte(Word address, Byte value);


    private:
    int _offset;
    int _file_fd;
    std::size_t _filemap_length;
    Byte *_filemap;

};
