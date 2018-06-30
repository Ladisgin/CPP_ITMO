cmake_minimum_required(VERSION 3.10)
project(hufflib)

set(CMAKE_CXX_STANDARD 14)

add_library(hufflib STATIC
        include/constants.h
        include/counter.h counter.cpp
        include/byte_vector.h byte_vector.cpp
        include/encoder.h encoder.cpp
        include/decoder.h decoder.cpp
        include/code_len.h code_len.cpp)