cmake_minimum_required(VERSION 3.22)
project(Pr1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Pr1 signal.c sigaction.c)
