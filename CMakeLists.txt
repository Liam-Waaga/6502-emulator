
cmake_minimum_required(VERSION 3.16)


project(
    6502-emulator
    VERSION 0.0.1
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_ARCHIVE_CREATE ON)
# set(CMAKE_CXX_ARCHIVE_FINISH ON)

add_subdirectory(src)

