cmake_minimum_required(VERSION 3.17)
project(PIN-2022)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)

add_executable(JSON_demo main.cpp)
