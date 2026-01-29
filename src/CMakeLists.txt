
include_directories(PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(log)
add_subdirectory(cpu)
add_subdirectory(vm)
add_subdirectory(common)

add_executable(
    6502
    main.cpp
)

target_link_libraries(
    6502
    PRIVATE
    log
)
