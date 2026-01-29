

add_subdirectory(devices)

add_library(
    vm
    vm.cpp
)

target_link_libraries(
    vm
    log
    devices
    common
)