//
// Created by Vladislav Kalugin on 23/06/2018.
//

#include "include/encoder.h"

encoder::encoder(counter &cntr) : huffman_tree(cntr.get_tree()) {
}

byte_vector encoder::encode(std::vector<byte> const &data) {
    byte_vector res;
    for (auto i : data) {
        if (huffman_tree[i].len == 0) {
            throw std::runtime_error("incorrect file");
        }
        res.push_back(huffman_tree[i]);
    }
    return res;
}

std::vector<std::pair<byte, code_len>> encoder::give_alphabet() {
    std::vector<std::pair<byte, code_len>> v;
    for (size_t i = 0; i <= std::numeric_limits<byte>::max(); i++) {
        if (huffman_tree[i].len != 0) {
            v.push_back(std::make_pair(static_cast<byte >(i), huffman_tree[i]));
        }
    }
    return v;
}
