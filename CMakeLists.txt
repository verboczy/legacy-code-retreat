cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_definitions(-Wall -pedantic -Wdeprecated -std=c++17)
# Rule for tests
add_executable(tests GameTest.cpp Game.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread)

# Rule for compiling whole project
add_executable(rungame Game.cpp GameRunner.cpp)