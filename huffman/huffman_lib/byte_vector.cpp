//
// Created by Vladislav Kalugin on 23/06/2018.
//

#include "include/byte_vector.h"

byte_vector::byte_vector() : data(1, static_cast<byte>(0)), last_size(0) {
}


void byte_vector::push_back(byte const &sym, size_t const &len) {
    data.back() |= (sym >> last_size);
    if (last_size + len > std::numeric_limits<byte>::digits) {
        data.resize(data.size() + 1);
        data.back() = static_cast<byte>(sym << (std::numeric_limits<byte>::digits - last_size));
        last_size = len + last_size - std::numeric_limits<byte>::digits;
    } else if (last_size + len == std::numeric_limits<byte>::digits) {
        data.resize(data.size() + 1);
        data.back() = 0;
        last_size = 0;
    } else {
        last_size += len;
    }
}

void byte_vector::push_back(byte const &sym) {
    push_back(sym, std::numeric_limits<byte>::digits);
}

void byte_vector::push_back(code_len const &sym) {
    size_t i = 1;
    for (; i <= (sym.len / std::numeric_limits<byte>::digits); i++) {
        push_back(static_cast<byte>((sym.code
                >> (std::numeric_limits<uint64_t>::digits - (i * std::numeric_limits<byte>::digits))) &
                                    std::numeric_limits<byte>::max()));
    }
    size_t re = sym.len % std::numeric_limits<byte>::digits;
    if (re) {
        push_back(static_cast<byte>((sym.code
                >> (std::numeric_limits<uint64_t>::digits - (i * std::numeric_limits<byte>::digits))) &
                                    std::numeric_limits<byte>::max()), re);
    }
}

void byte_vector::set_zero() {
    data.resize(1);
    data.back() = 0;
}
