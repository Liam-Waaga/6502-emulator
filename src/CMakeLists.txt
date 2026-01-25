

add_subdirectory(log)
add_subdirectory(vm)

add_executable(
    6502
    main.cpp
)

# set_target_properties(
#     6502
#     PROPERTIES LINKER_LANGUAGE CXX
# )


target_link_libraries(
    6502
    PRIVATE
    log
)

target_include_directories(
    6502
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)