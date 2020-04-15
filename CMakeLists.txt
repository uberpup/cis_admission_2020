cmake_minimum_required(VERSION 3.15)
project(cis_admission)

find_library(PTHREAD_LIBRARY pthread)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lpthread")

target_link_libraries(main ${PTHREAD_LIBRARY})
add_executable(cis_admission main.cpp server.h client.h server.cpp client.cpp syscall_data.h)