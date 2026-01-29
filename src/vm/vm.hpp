#pragma once


#include "common/common.hpp"
#include "devices/device.hpp"
#include <vector>



class VirtualMemory {
    public:
    VirtualMemory();
    ~VirtualMemory();
    
    void addDevice(Device dev);
    
    Byte read_byte(Word address);
    Word read_word(Word address);
    
    void write_byte(Word address, Byte value);
    void write_word(Word address, Word value);

    private:
    std::vector<Device> devices;
};