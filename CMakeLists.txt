cmake_minimum_required(VERSION 3.15)

set (CMAKE_C_STANDARD 99)

project(ircbot C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(src)
#add_subdirectory(test)
#add_subdirectory(vendor/googletest)
