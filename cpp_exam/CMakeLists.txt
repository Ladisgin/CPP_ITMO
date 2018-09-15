cmake_minimum_required(VERSION 2.8)

project(Fixed_vector)

include_directories(${FIXED_VECTOR_DIR} .)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -fno-omit-frame-pointer -D_GLIBCXX_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -flto -fvisibility=hidden")


add_executable(fixed_vector_test vector_tests.cpp fixed_vector.h base_vector.h doctest/doctest.h)