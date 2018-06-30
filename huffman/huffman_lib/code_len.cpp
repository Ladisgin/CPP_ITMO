//
// Created by Vladislav Kalugin on 23/06/2018.
//

#include "include/code_len.h"

bool operator<(code_len const &a, code_len const &b) {
    return (a.len == b.len ? a.code < b.code : a.len < b.len);
}
