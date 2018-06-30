//
// Created by Vladislav Kalugin on 23/06/2018.
//

#ifndef HUFFMAN_LIB_COUNTER_H
#define HUFFMAN_LIB_COUNTER_H

#include "constants.h"
#include "code_len.h"
#include <memory>

class counter {
private:
    struct code {
        size_t len;
        uint64_t sym;

        code() : len(0), sym(0) {}

        uint64_t give_code() const {
            return (sym << (std::numeric_limits<uint64_t>::digits - len));
        }

        code left() {
            code t;
            t.len = len + 1;
            t.sym = (sym << 1) | 1;
            return t;
        }

        code right() {
            code t;
            t.len = len + 1;
            t.sym = (sym << 1);
            return t;
        }
    };

    struct node {
        byte symbol;
        bool is_end;
        uint64_t count;
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;

        node() : symbol(0), is_end(false), count(0), left(nullptr), right() {}

        node(byte sym, uint64_t c) : symbol(sym), is_end(true), count(c), left(), right() {}

        ~node() = default;
    };

    uint64_t count[MAX_ALPHABET_LENGTH];
    uint64_t check_sum;

    void build_tree(const std::unique_ptr<node> &nd, std::vector<code_len> &huffman_tree, code cd);

public:
    counter();

    void update(std::vector<byte> const& next_bytes);

    std::vector<code_len> get_tree();
    
    uint64_t get_count_of_char();
};


#endif //HUFFMAN_LIB_COUNTER_H
