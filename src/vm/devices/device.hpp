#pragma once

#include "common.hpp"


class Device {
    public:
    Device(Word begin_address, Word end_address);
    virtual ~Device();

    /* the following address are absolute addresses, and _begin_address <= address < _end_address */
    virtual Byte read_byte(Word address);
    virtual Word read_word(Word address);
    
    virtual void write_byte(Word address, Byte value);
    virtual void write_word(Word address, Word value);

    Word get_begin_address();
    Word get_end_address();
    
    private:
    Word _begin_address;
    Word _end_address;
};