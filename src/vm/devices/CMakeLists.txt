

add_library(
    devices
    ram.cpp
    rom.cpp
    device.cpp
)

set_target_properties(
    devices
    PROPERTIES LINKER_LANGUAGE CXX
)

target_link_libraries(
    devices
    log
)

target_include_directories(
    devices
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)