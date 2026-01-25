

add_library(
    devices
    ram.c
    rom.c
    device.c
)


target_link_libraries(
    devices
    log
)

target_include_directories(
    devices
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)