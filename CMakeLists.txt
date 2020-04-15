cmake_minimum_required(VERSION 3.15)
project(cis_admission)

set(CMAKE_CXX_STANDARD 17)

add_executable(cis_admission main.cpp server.h client.h server.cpp client.cpp syscall_data.h)