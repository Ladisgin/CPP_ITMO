//
// Created by Vladislav Kalugin on 23/06/2018.
//

#ifndef HUFFMAN_CODE_LEN_H
#define HUFFMAN_CODE_LEN_H

#include "constants.h"
#include <cstdio>
#include <cstdint>

class code_len {
public:
    uint64_t code;
    size_t len;

    code_len() : code(0), len(0) {}

    code_len(uint64_t const &cd) : code(cd), len(static_cast<size_t>(std::numeric_limits<uint64_t>::digits)) {}

    code_len(uint64_t const &cd, size_t const &l) : code(cd), len(l ? l : 1) {}

    friend bool operator<(code_len const &a, code_len const &b);
};

bool operator<(code_len const &a, code_len const &b);

#endif //HUFFMAN_CODE_LEN_H
