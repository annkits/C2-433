cmake_minimum_required(VERSION 3.10)
project(StudentSort)

option(USE_STATIC "Build static library" ON)

if(USE_STATIC)
    add_library(alg STATIC alg.c)
    set_target_properties(alg PROPERTIES
        OUTPUT_NAME "alg"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )
else()
    add_library(alg SHARED alg.c)
    set_target_properties(alg PROPERTIES
        OUTPUT_NAME "alg"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        POSITION_INDEPENDENT_CODE ON
    )
endif()

add_executable(program main.c)

target_include_directories(program PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(program alg)

set_target_properties(program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)