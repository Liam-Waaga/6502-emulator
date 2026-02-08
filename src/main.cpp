

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
                    log(ERROR, "Argument '--config' requires argument");
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

            log(INFO, "Starting execution loop");
            cpu.start_execution_loop();
            log(INFO, "Execution loop stopped");
            log(INFO, "Performing cleanup");

            return 0;
        } else {
            logf(ERROR, "Unable to find config file \'%s\'", options.config_file.c_str());
            return 1;
        }
    } catch (std::exception& e) {
        logf(ERROR, "Uncaught exception \"%s\"", e.what());
        return 1;
    }
}