//
// Created by Vladislav Kalugin on 23/06/2018.
//

#include "include/decoder.h"

decoder::decoder(std::vector<std::pair<byte, code_len>> v) : current_state() {
    mp.resize(std::numeric_limits<byte>::max() + 1);
    for (auto i:v) {
        mp[i.second.len].insert({i.second.code, i.first});
    }
}

std::vector<byte> decoder::decode(std::vector<byte> v) {
    std::vector<byte> res;
    for (int i = 0; i < v.size(); i++) {
        for (size_t j = static_cast<size_t>(std::numeric_limits<byte>::digits); j > 0; j--) {
            current_state.len++;
            if (current_state.len > std::numeric_limits<uint64_t>::digits) {
                throw std::runtime_error("incorrect file");
            }
            current_state.code = (current_state.code << 1) | ((v[i] >> (j - 1)) & 1);
            auto k = mp[current_state.len].find(
                    current_state.code << (std::numeric_limits<uint64_t>::digits - current_state.len));
            if (k != mp[current_state.len].end()) {
                res.resize(res.size() + 1);
                res.back() = k->second;
                current_state.len = 0;
                current_state.code = 0;
            }
        }
    }
    return res;
}
