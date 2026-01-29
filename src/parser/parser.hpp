#pragma once


#include "vm/vm.hpp"

#include <filesystem>

namespace Parser {
    VirtualMemory parse_config(std::filesystem::path config_file);
}