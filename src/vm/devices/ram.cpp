

#include "ram.hpp"
#include "common.hpp"
#include "device.hpp"
#include "log.h"


#include <cstdlib>

RAM::RAM(Word begin_address, Word end_address)
    : _mem(nullptr) {
    set_addresses(begin_address, end_address);
    this->_mem = (Byte *) std::malloc(end_address - begin_address);
    if (!this->_mem) {
        log(ERROR, "Malloc failed");
        std::exit(1); /* no need to set _error because we just exit, leave it to the kernel to cleanup */
    }

}

RAM::~RAM() {
    std::free(this->_mem);
}

Byte RAM::read_byte(Word address) {
    if (address < get_begin_address() && address >= get_end_address()) {
        this->_error |= INDEX_OUT_OF_RANGE;
        logf(
            ERROR, "Index out of range. Wanted %d but must satisfy %d <= address < %d",
            address, get_begin_address(), get_end_address()
        );
        return 0;
    }
    return *(this->_mem + (address - this->get_begin_address()));
}

void RAM::write_byte(Word address, Byte value) {
    if (address < get_begin_address() && address >= get_end_address()) {
        this->_error |= INDEX_OUT_OF_RANGE;
        logf(
            ERROR, "Index out of range. Wanted %d but must satisfy %d <= address < %d",
            address, get_begin_address(), get_end_address()
        );
    } else {
        *(this->_mem + (address - this->get_begin_address())) = value;
    }
}