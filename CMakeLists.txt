
cmake_minimum_required(VERSION 3.16)


project(
    6502-emulator
    VERSION 0.0.1
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_compile_options(-Wall -Wextra -pedantic -Werror)

add_subdirectory(src)

