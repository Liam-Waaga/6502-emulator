#pragma once


#include "vm/vm.hpp"

#include <filesystem>

class CPU {

    public:
    CPU(std::filesystem::path config_file);
    ~CPU();

    void start_execution_loop();


    private:
    void do_cycle();




    VirtualMemory vm;
};