/*
 * Simple modular 6502 emulator written in c++
 * Copyright (C) 2026 N Liam Waaga
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

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