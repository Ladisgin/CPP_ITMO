cmake_minimum_required(VERSION 3.10)
project(huffman)

add_executable(encode utils/encode.cpp)
add_executable(decode utils/decode.cpp)
add_executable(huffman_test test/encode_decode_test.cpp)

include_directories(huffman_lib/include)
add_subdirectory(huffman_lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -fno-omit-frame-pointer -D_GLIBCXX_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -flto -fvisibility=hidden")


target_link_libraries(encode hufflib)
target_link_libraries(decode hufflib)
target_link_libraries(huffman_test hufflib)