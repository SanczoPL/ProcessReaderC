cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(processreader VERSION 0.0.1 DESCRIPTION "processreader" LANGUAGES C)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

configure_file(test/test_proc_status.txt ${CMAKE_BINARY_DIR}/test_proc_status.txt)
configure_file(test/test_proc_status.txt ${CMAKE_BINARY_DIR}/bin/142804)

add_subdirectory(cmocka-1.1.3)

add_executable(processreader src/main.c src/processreader.c src/queue.c)

add_executable(test 
test/test_proc_status.txt 
test/test.c 
test/test_processreader.h 
test/test_queue.h 
src/processreader.c src/queue.c)

target_link_libraries(processreader)

target_link_libraries(test cmocka)

set_property(TARGET processreader PROPERTY C_STANDARD 99)
