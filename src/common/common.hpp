#pragma once


typedef unsigned char Byte;
typedef unsigned short Word;


#include <string>

struct Options {
    std::string config_file = "6502.ini";
};

extern Options options;
