
cmake_minimum_required(VERSION 3.16)


project(
    6502-emulator
    VERSION 0.0.1
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

