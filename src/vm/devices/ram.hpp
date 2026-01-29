#pragma once

#include "vm/devices/device.hpp"


class RAM : Device {
    public:
    RAM(Word begin_address, Word end_address);
    ~RAM();
    
    Byte read_byte(Word address) const;

    void write_byte(Word address, Byte value);


    private:
    Byte *_mem;
};
