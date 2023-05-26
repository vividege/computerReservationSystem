cmake_minimum_required(VERSION 3.22)

set(This ComputerReserveSystem)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    include/student.h
    include/reservation.h
)
set(Sources
    src/student.cpp
    src/reservation.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)