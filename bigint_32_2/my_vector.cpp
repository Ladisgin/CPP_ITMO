//
// Created by Vladislav Kalugin on 10/06/2018.
//

#include "my_vector.h"

void my_vector::reserve(size_t sz) {
    copy_check();
    if (sz <= SMALL_SIZE && data_capacity <= SMALL_SIZE) {
        _data = std::make_shared<uint32_t *>(union_data.small_data);
        data_capacity = SMALL_SIZE;
        is_big = false;
    }
    if (data_capacity < sz) {
        data_capacity = std::max(data_capacity * 2, sz);
        auto new_data = static_cast <uint32_t *> (operator new(sizeof(uint32_t) * data_capacity));
        if (_data != nullptr) {
            std::copy(*_data, *_data + data_size, new_data);
        }
        union_data.big_data = new_data;
        _data = std::make_shared<uint32_t *>(union_data.big_data);
        is_big = true;
    }
}

void my_vector::resize(size_t sz) {
    if (sz <= SMALL_SIZE && data_capacity <= SMALL_SIZE) {
        _data = std::make_shared<uint32_t *>(union_data.small_data);
        data_capacity = SMALL_SIZE;
        is_big = false;
    } else if (data_capacity < sz) {
        data_capacity = std::max(static_cast <size_t> (data_capacity * 2), sz);
        union_data.big_data = static_cast <uint32_t *> (operator new(sizeof(uint32_t) * data_capacity));
        _data = std::make_shared<uint32_t *>(union_data.big_data);
        is_big = true;
    }
    data_size = sz;
}

void my_vector::resize(size_t sz, uint32_t val) {
    resize(sz);
    for (int i = 0; i < sz; i++) {
        (*_data)[i] = val;
    }
}

my_vector::my_vector(size_t sz, uint32_t val) : data_capacity(0), data_size(0), is_big(false) {
    resize(sz, val);
}

my_vector::my_vector(size_t sz) : data_capacity(0), data_size(0), is_big(false) {
    resize(sz);
}

my_vector::my_vector() : data_capacity(0), data_size(0), is_big(false) {
    resize(0);
}

size_t my_vector::size() const {
    return data_size;
}

uint32_t my_vector::back() const {
    return (*_data)[data_size - 1];
}

uint32_t &my_vector::back() {
    copy_check();
    return (*_data)[data_size - 1];
}

void my_vector::push_back(uint32_t val) {
    copy_check();
    reserve(data_size + 1);
    data_size++;
    back() = val;
}

uint32_t my_vector::operator[](size_t pos) const {
    return (*_data)[pos];
}

uint32_t &my_vector::operator[](size_t pos) {
    copy_check();
    return (*_data)[pos];
}

void my_vector::pop_back() {
    copy_check();
    reserve(data_size - 1);
    data_size--;
}

bool my_vector::empty() {
    return data_size == 0;
}

my_vector &my_vector::operator=(my_vector const &other) {
    if (other.data_size > SMALL_SIZE) {
        _data = other._data;
        data_capacity = other.data_capacity;
        data_size = other.data_size;
        is_big = other.is_big;
    } else {
        if (_data != nullptr) {
            std::copy(*other._data, *other._data + other.data_size, union_data.small_data);
        }
        data_size = other.data_size;
        _data  = std::make_shared<uint32_t *>(union_data.small_data);
        data_capacity = SMALL_SIZE;
        is_big = false;
    }
    return *this;
}

my_vector::my_vector(my_vector const &other) {
    *this = other;
}

void my_vector::copy_check() {
    if (!_data.unique()) {
        data_capacity = data_size;
        auto new_data = static_cast <uint32_t *> (operator new(sizeof(uint32_t) * data_capacity));
        if (_data != nullptr) {
            std::copy(*_data, *_data + data_size, new_data);
        }
        union_data.big_data = new_data;
        _data  = std::make_shared<uint32_t *>(union_data.big_data);
        is_big = true;
    }
}
