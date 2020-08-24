cmake_minimum_required(VERSION 3.17)
project(TCP_Portable_Server__Calculator_ C)

set(CMAKE_C_STANDARD 99)
link_libraries(ws2_32 wsock32)

add_executable(TCP_Portable_Server__Calculator_ main.c serverHeader.h serverUtilities.h)
