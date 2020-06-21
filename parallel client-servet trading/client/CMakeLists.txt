cmake_minimum_required(VERSION 3.15)
project(client_tradingSystem)

set(CMAKE_CXX_STANDARD 11)

add_executable(client_tradingSystem main.cpp SClientStructures.h CClientTrader.cpp CClientTrader.h)