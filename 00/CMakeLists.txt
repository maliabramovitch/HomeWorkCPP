cmake_minimum_required(VERSION 3.23)
project(01 C)

set(CMAKE_C_STANDARD 99)

add_executable(01 main.c Passenger.c Passenger.h ADTStack.h ADTStack.c)
