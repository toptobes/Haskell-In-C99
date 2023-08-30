cmake_minimum_required(VERSION 3.23)
project(functionalC C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS ON)

add_executable(functionalC main.c include/closures.h include/types.h)
