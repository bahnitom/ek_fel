cmake_minimum_required(VERSION 3.16)
project(hw02a)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw02a
        hw02a/main.c)

project(hw02b)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw02b
        hw02b/main.c)

project(hw03a)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw03a
        hw03a/main.c)

project(hw03b)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw03b
        hw03b/main.c)

project(hw04)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw04
        hw04/main.c)

project(hw05)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw05
        hw05/main.c)

project(hw07)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw07
        hw07/main.c)

project(my_codes_working)
set(CMAKE_CXX_STANDARD 14)
add_executable(my_codes_working
        my_codes_working/main.c)

project(hw08)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_STANDARD 14)
add_executable(hw08
        hw08/main.c)
target_link_libraries(hw08 m)

project(hw09)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw09
        hw09/main.c)

project(hw09_tmp)
set(CMAKE_CXX_STANDARD 14)
add_executable(hw09_tmp
        hw09/6-4_2.c)