
#include "cpu/cpu.hpp"
#include "parser/parser.hpp"
#include "log/log.h"

#include <filesystem>

CPU::CPU(std::filesystem::path config_file) {
    this->vm = Parser::parse_config(config_file);
}