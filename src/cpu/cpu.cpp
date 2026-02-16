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

#include "cpu.hpp"
#include "log.h"
#include "parser/parser.hpp"
#include <string>

/* returns the long double parsed from section[field]. if the parsing fails, it returns the _default value (default is a keyword)*/
inline long double get_long_double_or_default(const INI_Parser::INI_Section& section, std::string field, long double _default) {
    try {
        return std::stod(section[field]);
    } catch (...) {
        if (section[field] != "") {
            Logger::logf(Logger::WARN, "Field \"%s\" has invalid value \"%s\". Using default value %fL.", field.c_str(), section[field].c_str(), _default);
        }
        return _default;
    }
}

void CPU::start_execution_loop() {
    CPU::do_cycle();
    if (CPU::get_interrupt() != CPU::Interrupt::INTERRUPT_NONE) {
        /* TODO: interrupt handling */
    }
}

CPU::CPU(INI_Parser::INI_Data config) {
    /* TODO: actually properly initialize the cpu state to its correct values rather than zeros */
    this->_cpu_state = {
        ._a = 0u,
        ._x = 0u,
        ._y = 0u,
        ._pc = 0u,
        ._sp = 0u,
        ._flags = 0u,
    };

    this->_interrupt = CPU::Interrupt::INTERRUPT_NONE;


    bool hasParsedGlobal = false;

    for (auto section : config) {
        std::string name = section.get_section_name();
        if (name == "") {
            if (!hasParsedGlobal) {
                Logger::log(Logger::WARN, "Found section without name which isn't the global section. Ignoring.");
                continue;
            }
            hasParsedGlobal = true;

            this->_frequency = get_long_double_or_default(section, "frequency", 1000000);
        } else if (name == "rom") {
            /* TODO: implement adding a rom to the vm */
        } else if (name == "ram") {
            /* TODO: implement adding a ram to the vm */
        } else {
            Logger::logf(Logger::WARN, "Found section with unkown name \"%s\", ignoring the whole section", name.c_str());
        }
    }
}