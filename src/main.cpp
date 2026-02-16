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



#include "log/log.h"
#include "cpu/cpu.hpp"
#include "common/common.hpp"
#include "parser/parser.hpp"

#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>

Options options;

[[noreturn]] void print_help() {
    try {
        std::printf(
            "Simple 6502 emulator with support for custom devices\n"
            "Version: " VERSION " built from commit " GIT_HASH "\n"
            "Arguments:\n"
            "  --help           - Print this help message (includes version)\n"
            "  --version        - Print this help message (includes version)\n"
            "  --config <file>  - Specify the config file\n"
            "\n"
        );
    } catch (...) {}
    std::exit(1);
}

void parse_config(int argc, char ** argv) {
    if (argc > 1) {
        for (std::size_t i = 0; i < (std::size_t) argc; i++) {
            std::string arg = argv[i];
            if (arg == "--help") {
                print_help();
            } else if (arg == "--version") {
                print_help();
            } else if (arg == "--config") {
                if (i + 1 < (std::size_t) argc) {
                    options.config_file = argv[++i];
                } else {
                    Logger::log(Logger::ERROR, "Argument '--config' requires argument");
                    printf("\n");
                    print_help();
                }
            }
        }
    }
}

int main(int argc, char ** argv) {
    parse_config(argc, argv);

    try {
        if (std::filesystem::exists(options.config_file)) {
            auto parsed_config = INI_Parser::ini_parse(std::filesystem::path(options.config_file));
            CPU cpu = CPU(parsed_config);

            Logger::log(Logger::INFO, "Starting execution loop");
            cpu.start_execution_loop();
            Logger::log(Logger::INFO, "Execution loop stopped");
            Logger::log(Logger::INFO, "Performing cleanup");

            return 0;
        } else {
            Logger::logf(Logger::ERROR, "Unable to find config file \'%s\'", options.config_file.c_str());
            return 1;
        }
    } catch (std::exception& e) {
        Logger::logf(Logger::ERROR, "Uncaught exception \"%s\"", e.what());
        return 1;
    }
}