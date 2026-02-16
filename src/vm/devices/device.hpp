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

#pragma once

#include "common/common.hpp"


class Device {
    public:
    Device();
    virtual ~Device();

    /* the following address are absolute addresses, and _begin_address <= address < _end_address */
    /* the following should not error if in the allowed address range unless something exceptional happens */
    virtual Byte read_byte(Word address) const = 0;
    /* little endian */
    /* not virtual because it is the same no matter what, just uses the byte version under the hood */
    Word read_word(Word address) const;

    virtual void write_byte(Word address, Byte value) = 0;
    void write_word(Word address, Word value);

    Word get_begin_address() const;
    Word get_end_address() const;

    bool can_access_address(Word address) const;


    protected:
    void set_addresses(Word begin_address, Word end_address);

    private:
    Word _begin_address;
    Word _end_address;

};
