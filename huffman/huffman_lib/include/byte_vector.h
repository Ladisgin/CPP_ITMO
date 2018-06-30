//
// Created by Vladislav Kalugin on 23/06/2018.
//

#ifndef HUFFMAN_LIB_BYTE_VECTOR_H
#define HUFFMAN_LIB_BYTE_VECTOR_H

#include "constants.h"
#include "code_len.h"

class byte_vector {
private:
public:
    std::vector<byte> data;
    size_t last_size;

    byte_vector();

    void push_back(byte const &sym, size_t const &len);

    void push_back(byte const &sym);

    void push_back(code_len const &sym);
};


#endif //HUFFMAN_LIB_BYTE_VECTOR_H
