

#include "vm/devices/ram.hpp"
#include "common/common.hpp"


#include <new>
#include <stdexcept>

RAM::RAM(Word begin_address, Word end_address)
    : _mem(nullptr) {
    set_addresses(begin_address, end_address);
    this->_mem = (Byte *) std::malloc(end_address - begin_address);
    if (!this->_mem) {
        throw std::bad_alloc();
    }

}

RAM::~RAM() {
    std::free(this->_mem);
}

Byte RAM::read_byte(Word address) const {
    if (address < get_begin_address() && address >= get_end_address()) {
        throw std::out_of_range("Index out of range");
    }
    return *(this->_mem + (address - this->get_begin_address()));
}

void RAM::write_byte(Word address, Byte value) {
    if (address < get_begin_address() && address >= get_end_address()) {
        throw std::out_of_range("Index out of range");
    } else {
        *(this->_mem + (address - this->get_begin_address())) = value;
    }
}
