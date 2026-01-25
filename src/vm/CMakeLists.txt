

add_subdirectory(devices)

add_library(
    vm
    vm.cpp
)

set_target_properties(
    vm
    PROPERTIES LINKER_LANGUAGE CXX
)

target_link_libraries(
    vm
    log
    devices
)

target_include_directories(
    vm
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

