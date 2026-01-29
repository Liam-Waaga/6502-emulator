
add_library(
    cpu
    cpu.cpp
)


target_link_libraries(
    cpu
    vm
    log
)