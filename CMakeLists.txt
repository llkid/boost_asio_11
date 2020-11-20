cmake_minimum_required(VERSION 3.16)
project(boost_asio_11)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(handler_memory)
include_directories(/usr/include)

aux_source_directory(handler_memory HM_SOURCE)
message(STATUS "handler_memory 下源文件有: ${HM_SOURCE}")
add_library(SRC SHARED ${HM_SOURCE})
target_link_libraries(SRC pthread boost_system boost_filesystem)

add_executable(boost_asio_11 main.cpp ${HM_SOURCE} handler_memory/handle_allocator.h handler_memory/custom_alloc_handler.h handler_memory/session.h handler_memory/server.cpp handler_memory/server.h)
target_link_libraries(boost_asio_11 SRC)