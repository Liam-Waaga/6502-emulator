#pragma once


#include "parser/parser.hpp"
#include "vm/vm.hpp"

#include <vector>

class CPU {

    public:
    CPU(std::vector<INI_Parser::INI_Section> config);
    ~CPU();

    void start_execution_loop();


    private:
    void do_cycle();
    bool check_for_interrupts();


    VirtualMemory vm;
};