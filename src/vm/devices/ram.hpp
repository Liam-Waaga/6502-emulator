#pragma once
#include "device.hpp"


class RAM : Device {
    public:
    RAM(Word begin_address, Word end_address);
    ~RAM();
    
    Byte read_byte(Word address);
    Word read_word(Word address);


    void write_byte(Word address, Byte value);
    void write_word(Word address, Word value);

    private:
    void *_mem;
};