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


#include "parser/parser.hpp"
#include "vm/vm.hpp"

#include <cstdint>
#include <sys/types.h>

class CPU {

    public:
    CPU(INI_Parser::INI_Data config);
    ~CPU();

    void start_execution_loop();


    struct CPU_State{
        uint16_t _a;
        uint16_t _x;
        uint16_t _y;
        uint16_t _pc;
        uint8_t _sp;
        /* in this order, from left to right (MSB->LSB), the flags are */
        /* Negative, Overflow, Break, Decimal, Interrupt Disable, Zero, Carry */
        uint8_t _flags;

        void set_negative() {
            this->_flags |= 0b01000000;
        }
        void unset_negative() {
            this->_flags &= 0b10111111;
        }
        bool get_negative() {
            return this->_flags & 0b01000000;
        }

        void set_overflow() {
            this->_flags |= 0b00100000;
        }
        void unset_overflow() {
            this->_flags &= 0b11011111;
        }
        bool get_overflow() {
            return this->_flags & 0b00100000;
        }

        void set_break() {
            this->_flags |= 0b00010000;
        }
        void unset_break() {
            this->_flags &= 0b11101111;
        }
        bool get_break() {
            return this->_flags & 0b00010000;
        }

        void set_decimal() {
            this->_flags |= 0b00001000;
        }
        void unset_decimal() {
            this->_flags &= 0b11110111;
        }
        bool get_decimal() {
            return this->_flags & 0b00001000;
        }

        void set_interrupt_disable() {
            this->_flags |= 0b00000100;
        }
        void unset_interrupt_disable() {
            this->_flags &= 0b11111011;
        }
        bool get_interrupt_disable() {
            return this->_flags & 0b00000100;
        }

        void set_zero() {
            this->_flags |= 0b00000010;
        }
        void unset_zero() {
            this->_flags &= 0b11111101;
        }
        bool get_zero() {
            return this->_flags & 0b00000010;
        }

        void set_carry() {
            this->_flags |= 0b00000001;
        }
        void unset_carry() {
            this->_flags &= 0b11111110;
        }
        bool get_carry() {
            return this->_flags & 0b00000001;
        }

    };

    enum Interrupt {
        INTERRUPT_NONE,
        INTERRUPT_REQUEST,
        INTERRUPT_NON_MASKABLE,
        INTERRUPT_RESET,
    };


    Interrupt get_interrupt() {
        return this->_interrupt;
    }
    void interrupt(Interrupt interrupt) {
        this->_interrupt = interrupt;
    }



    private:
    void do_cycle();

    CPU_State _cpu_state;
    Interrupt _interrupt;

    double _frequency;

    VirtualMemory _vm;
};