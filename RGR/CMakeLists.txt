cmake_minimum_required(VERSION 3.10)
project(Vigenere C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

# Создание динамической библиотеки
add_library(vigenere SHARED vigenere.c)

# Создание исполняемого файла
add_executable(vigenera main.c)
target_link_libraries(vigenera vigenere)

enable_testing()

find_library(CMOCKA_LIBRARY NAMES cmocka libcmocka HINTS /usr/local/lib)
find_path(CMOCKA_INCLUDE_DIR cmocka.h HINTS /usr/local/include)

if (NOT CMOCKA_LIBRARY OR NOT CMOCKA_INCLUDE_DIR)
    message(FATAL_ERROR "CMocka not found. Ensure it is installed in /usr/local")
endif()

include_directories(${CMOCKA_INCLUDE_DIR})

add_executable(test_vigenere tests/test_vigenere.c)
target_link_libraries(test_vigenere vigenere ${CMOCKA_LIBRARY})

add_test(NAME VigenereTests COMMAND test_vigenere)
