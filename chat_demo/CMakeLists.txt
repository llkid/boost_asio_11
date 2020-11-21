cmake_minimum_required(VERSION 3.16)
project(chat_demo)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(src)
include_directories(test)

aux_source_directory(src/client CLIENT_SOURCE)
aux_source_directory(src/server SERVER_SOURCE)
message(STATUS "src/chat/client 有源文件: ${CLIENT_SOURCE}")
message(STATUS "src/chat/server 有源文件: ${SERVER_SOURCE}")

add_library(SRC SHARED ${CLIENT_SOURCE} ${SERVER_SOURCE})
target_link_libraries(SRC pthread boost_system)

file(GLOB_RECURSE TESTS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/TEST*")
message(STATUS "test 有源文件: ${TEST_SOURCES}")
foreach(TEST IN LISTS TESTS)
    message(STATUS ">> ${TEST}")
    get_filename_component(filename ${TEST} NAME_WE)
    add_executable(${filename} ${TEST})
    add_dependencies(${filename} SRC)
    target_link_libraries(${filename} SRC)
endforeach()

add_executable(chat_demo main.cpp)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)