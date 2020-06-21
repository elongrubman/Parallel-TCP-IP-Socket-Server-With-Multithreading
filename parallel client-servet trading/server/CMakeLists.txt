cmake_minimum_required(VERSION 2.8)
project(trading_system_tranning)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_compile_options(-std=c++11)

add_executable(trading_system_tranning main.cpp CTradingSystem.cpp CTradingSystem.h STradingSystemStructures.h)

find_package(Threads)
target_link_libraries(trading_system_tranning ${CMAKE_THREAD_LIBS_INIT})