#pragma once

#include "common.hpp"


class Device {
    public:
    Device();
    virtual ~Device();

    /* the following address are absolute addresses, and _begin_address <= address < _end_address */
    /* the following should not error if in the allowed address range unless something exceptional happens */
    virtual Byte read_byte(Word address) const;
    /* little endian */
    /* not virtual because it is the same no matter what, just uses the byte version */
    Word read_word(Word address) const;
    
    virtual void write_byte(Word address, Byte value);
    /* little endian */
    /* not virtual because it is the same no matter what, just uses the byte version */
    void write_word(Word address, Word value);
    
    Word get_begin_address() const;
    Word get_end_address() const;

    bool can_access_address(Word address) const;

    int get_error() const;
    void clear_error();

    
    protected:
    enum Error {
        INDEX_OUT_OF_RANGE = 1,
        SET_BAD_ADDRESS = INDEX_OUT_OF_RANGE << 1,
        FILE_NOT_EXIST = SET_BAD_ADDRESS << 1,
        MMAP_FAILED = FILE_NOT_EXIST << 1,
    };
    mutable unsigned int _error;
    void set_addresses(Word begin_address, Word end_address);
    
    private:
    Word _begin_address;
    Word _end_address;
    
};
