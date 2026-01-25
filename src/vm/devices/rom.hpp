#pragma once

#include "device.hpp"
#include <filesystem>

class ROM : Device {
    public:
    /* end_address is infered from the files length */
    ROM(Word begin_address, std::filesystem::path file);
    ~ROM();
    
    Byte read_byte(Word address);
    Word read_word(Word address);


    void write_byte(Word address, Byte value);
    void write_word(Word address, Word value);

    private:
    void *_filemap;

};