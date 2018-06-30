//
// Created by Vladislav Kalugin on 23/06/2018.
//

#ifndef HUFFMAN_LIB_DECODER_H
#define HUFFMAN_LIB_DECODER_H

#include <map>
#include "constants.h"
#include "code_len.h"
#include "byte_vector.h"


class decoder {
private:
    std::vector<std::map<code_len, byte>> mp;
    code_len current_state;
public:
    decoder() = delete;

    decoder(std::vector<std::pair<byte, code_len>>);

    std::vector<byte> decode(std::vector<byte> v);
};


#endif //HUFFMAN_LIB_DECODER_H
