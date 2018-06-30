//
// Created by Vladislav Kalugin on 23/06/2018.
//

#ifndef HUFFMAN_LIB_ENCODER_H
#define HUFFMAN_LIB_ENCODER_H

#include "counter.h"
#include "byte_vector.h"

class encoder {
private:
    std::vector<code_len> huffman_tree;
public:
    encoder() = delete;

    encoder(counter &cntr);

    byte_vector encode(std::vector<byte> data);

    std::vector<std::pair<byte, code_len>> give_alphabet();
};


#endif //HUFFMAN_LIB_ENCODER_H
