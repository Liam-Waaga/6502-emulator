#pragma once


#include "vm/vm.hpp"

#include <filesystem>

class CPU {

    public:
    CPU(std::filesystem::path config_file);

    void start_execution_loop();


    private:
    ~CPU();
    void do_cycle();




    VirtualMemory vm;
};