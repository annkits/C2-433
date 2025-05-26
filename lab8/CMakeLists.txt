cmake_minimum_required(VERSION 3.10)
project(IndexArrayTest C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

add_library(index_array src/index_array.c)

add_executable(index_array_test tests/index_array_test.c)
target_include_directories(index_array_test PRIVATE ${CHECK_INCLUDE_DIRS} src)
target_link_libraries(index_array_test PRIVATE index_array ${CHECK_LIBRARIES})

enable_testing()
add_test(NAME IndexArrayTests COMMAND index_array_test)