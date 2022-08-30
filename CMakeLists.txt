cmake_minimum_required(VERSION 3.16)

project(memmulator)

add_library(memmulator 
    src/mem.cpp
    src/memMap.cpp
)

target_include_directories(memmulator PRIVATE src/)
target_include_directories(memmulator PUBLIC include/)