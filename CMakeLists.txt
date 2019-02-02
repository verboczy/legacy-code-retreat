cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_definitions(-Wall -pedantic -Wdeprecated -std=c++17)
add_executable(executeTests GameTest.cpp Game.cpp)
target_link_libraries(executeTests ${GTEST_LIBRARIES} pthread)