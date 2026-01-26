#pragma once
#include "device.hpp"


class RAM : Device {
    public:
    RAM(Word begin_address, Word end_address);
    ~RAM();
    
    Byte read_byte(Word address);

    void write_byte(Word address, Byte value);


    private:
    Byte *_mem;
};