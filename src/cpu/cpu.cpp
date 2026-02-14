
#include "cpu.hpp"
#include "vm/vm.hpp"

void CPU::start_execution_loop() {
    CPU::do_cycle();
    if (CPU::get_interrupt() != CPU::Interrupt::INTERRUPT_NONE) {
        /* TODO: interrupt handling */
    }
}

CPU::CPU(INI_Parser::INI_Data config) {
    /* TODO: actually properly initialize the cpu state to its correct values */
    this->_cpu_state = {
        ._a = 0u,
        ._x = 0u,
        ._y = 0u,
        ._pc = 0u,
        ._sp = 0u,
        ._flags = 0u,
    };

    this->_interrupt = CPU::Interrupt::INTERRUPT_NONE;

    (void) config; /* supress unused parameter for now */
}