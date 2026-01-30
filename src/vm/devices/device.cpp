

#include "vm/devices/device.hpp"
#include "common/common.hpp"
#include <stdexcept>


Device::Device() {
    this->_begin_address = 0;
    this->_end_address = 0;
}

void Device::set_addresses(Word begin_address, Word end_address) {
    if (begin_address >= end_address) {
        throw std::out_of_range("Bad address");
    }
    this->_begin_address = begin_address;
    this->_end_address = end_address;
}

Word Device::get_begin_address() const{
    return this->_begin_address;
}

Word Device::get_end_address() const {
    return this->_end_address;
}

int Device::get_error() const {
    return this->_error;
}

bool Device::can_access_address(Word address) const {
    return address >= _begin_address && address < _end_address;
}

Word Device::read_word(Word address) const {
    return (Word) read_byte(address) | read_byte(address + 1) << 8;
}

void Device::write_word(Word address, Word value) {
    write_byte(address, (Byte) value);
    write_byte(address + 1, (Byte) (value >> 8));
}