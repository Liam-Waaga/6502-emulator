

add_subdirectory(log)
add_subdirectory(vm)

add_executable(
    6502
    main.c
)

target_link_libraries(
    6502
    PRIVATE
    log
)

target_include_directories(
    6502
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)