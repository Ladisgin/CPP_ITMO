//
// Created by Vladislav Kalugin on 23/06/2018.
//

#ifndef HUFFMAN_LIB_CONSTANTS_H
#define HUFFMAN_LIB_CONSTANTS_H

#include <vector>
#include <exception>
#include <map>
#include <limits>
#include <cstdint>

typedef unsigned char byte;

const int MAX_ALPHABET_LENGTH = std::numeric_limits<byte>::max() + 1;

const size_t READ_BLOCK = 4096 * 2;

#endif //HUFFMAN_LIB_CONSTANTS_H
