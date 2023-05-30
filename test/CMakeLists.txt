cmake_minimum_required(VERSION 3.22)

set(This studentTest)

set(Sources
    studentTest.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    gmock_main
    ComputerReserveSystem
)

add_test(
    NAME ${This}
    COMMAND ${This}
)