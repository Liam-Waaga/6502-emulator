

add_subdirectory(device)

add_library(
    vm
    vm.c
)

target_link_libraries(
    vm
    log
    device
)

target_include_directories(
    vm
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)