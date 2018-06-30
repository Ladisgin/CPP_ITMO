//
// Created by Vladislav Kalugin on 23/06/2018.
//

#include "include/counter.h"
#include <algorithm>

counter::counter() : check_sum(0) {
    for (int i = 0; i < MAX_ALPHABET_LENGTH; i++) {
        count[i] = 0;
    }
}

void counter::update(std::vector<byte> const &next_bytes) {
    check_sum += next_bytes.size();
    for (auto i:next_bytes) {
        count[i]++;
    }
}

std::vector<code_len> counter::get_tree() {
    std::vector<std::unique_ptr<node>> nodes;
    for (size_t i = 0; i < MAX_ALPHABET_LENGTH; i++) {
        if (count[i]) {
            nodes.push_back(std::unique_ptr<node>(new node(static_cast<byte >(i), count[i])));
        }
    }
    while (nodes.size() > 1) {
        std::sort(nodes.begin(), nodes.end(),
                  [](const std::unique_ptr<node> &a, const std::unique_ptr<node> &b) -> bool {
                      return a->count > b->count;
                  });
        std::unique_ptr<node> new_node(new node());
        new_node->count = nodes[nodes.size() - 1]->count + nodes[nodes.size() - 2]->count;
        new_node->left.swap(nodes[nodes.size() - 1]);
        new_node->right.swap(nodes[nodes.size() - 2]);
        nodes.pop_back();
        nodes.back().swap(new_node);
    }

    std::vector<code_len> huffman_tree(std::numeric_limits<byte>::max() + 1, code_len());

    if (nodes.size() == 1) {
        build_tree(nodes[0], huffman_tree, code());
    }
    return huffman_tree;
}

void
counter::build_tree(const std::unique_ptr<counter::node> &nd, std::vector<code_len> &huffman_tree, code cd) {
    if (nd) {
        if (nd->is_end) {
            huffman_tree[nd->symbol] = code_len(cd.give_code(), cd.len);
        } else {
            build_tree(nd->left, huffman_tree, cd.left());
            build_tree(nd->right, huffman_tree, cd.right());
        }
    }
}

uint64_t counter::get_count_of_char() {
    return check_sum;
}
