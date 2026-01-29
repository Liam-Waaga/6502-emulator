

add_library(
    devices
    ram.cpp
    rom.cpp
    device.cpp
)


target_link_libraries(
    devices
    log
)