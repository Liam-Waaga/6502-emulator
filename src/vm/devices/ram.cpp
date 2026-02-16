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
