//
// Created by Vladislav Kalugin on 10/06/2018.
//

#include "my_vector.h"
#include <iostream>

data_struct::data_struct() : size(0), capacity(SMALL_SIZE), is_big(false) {
}

data_struct::~data_struct() {
    if (is_big) {
        delete[] union_data.big_data;
    }
}

void data_struct::ensure_capacity(size_t sz) {
    if (sz > capacity) {
        capacity = std::max(sz, capacity * 2);
        auto new_int = new uint32_t[capacity];
        if (is_big) {
            std::copy(union_data.big_data, union_data.big_data + size, new_int);
        } else {
            std::copy(union_data.small_data, union_data.small_data + size, new_int);
        }
        if (is_big) {
            delete[] union_data.big_data;
        }
        union_data.big_data = new_int;
        is_big = true;
    } else if (sz <= SMALL_SIZE && is_big) {
        capacity = SMALL_SIZE;
        auto old_data_pointer = union_data.big_data;
        std::copy(old_data_pointer, old_data_pointer + SMALL_SIZE, union_data.small_data);
        delete[] old_data_pointer;
        is_big = false;
    }
    size = sz;
}


//main part
void my_vector::data_copy() {
    if (!_data.unique()) {
        if (_old_data) {
            _data.swap(_old_data);
            _data->ensure_capacity(_old_data->size);
            std::copy(_old_data->union_data.big_data, _old_data->union_data.big_data + _old_data->size,
                      _data->union_data.big_data);
            _old_data.reset();
        } else {
            auto old_data_pointer = _data->union_data.big_data;
            size_t sz = _data->size;
            _data.reset(new data_struct());
            _data->ensure_capacity(sz);
            std::copy(old_data_pointer, old_data_pointer + sz, _data->union_data.big_data);
        }
    }
}


void my_vector::data_without_copy() {
    if (!_data.unique()) {
        if(_old_data) {
            _data.swap(_old_data);
            _old_data.reset();
        } else {
            _data.reset(new data_struct());;
        }

    }
}

my_vector::my_vector() : is_copy(false) {
    _data.reset(new data_struct());
}

my_vector::my_vector(my_vector const &other) {
    other._data->ensure_capacity(other._data->size);
    if (other._data->is_big) {
        _old_data = other._data;
        _data.swap(_old_data);
        is_copy = true;
    } else {
        _data->ensure_capacity(other._data->size);
        std::copy(other._data->union_data.small_data, other._data->union_data.small_data + other._data->size,
                  _data->union_data.small_data);
        is_copy = false;
    }
}

my_vector::my_vector(size_t sz) : is_copy(false) {
    _data.reset(new data_struct());
    _data->ensure_capacity(sz);
}

my_vector::my_vector(size_t sz, uint32_t val) : is_copy(false) {
    _data.reset(new data_struct());
    resize(sz, val);
}

void my_vector::resize(size_t sz) {
    data_without_copy();
    _data->ensure_capacity(sz);
}

void my_vector::resize(size_t sz, uint32_t val) {
    data_without_copy();
    _data->ensure_capacity(sz);
    if (_data->is_big) {
        for (size_t i = 0; i < sz; i++) {
            _data->union_data.big_data[i] = val;
        }
    } else {
        for (size_t i = 0; i < sz; i++) {
            _data->union_data.small_data[i] = val;
        }
    }
}

size_t my_vector::size() const {
    return _data->size;
}

void my_vector::push_back(uint32_t val) {
    data_copy();
    _data->ensure_capacity(_data->size + 1);
    if (_data->is_big) {
        _data->union_data.big_data[_data->size - 1] = val;
    } else {
        _data->union_data.small_data[_data->size - 1] = val;
    }
}

uint32_t my_vector::operator[](size_t pos) const {
    if (_data->is_big) {
        return _data->union_data.big_data[pos];
    } else {
        return _data->union_data.small_data[pos];
    }
}

uint32_t &my_vector::operator[](size_t pos) {
    data_copy();
    if (_data->is_big) {
        return _data->union_data.big_data[pos];
    } else {
        return _data->union_data.small_data[pos];
    }
}

void my_vector::pop_back() {
    data_copy();
    _data->ensure_capacity(_data->size - 1);
}

my_vector &my_vector::operator=(my_vector const &other) {
    other._data->ensure_capacity(other._data->size);
    if (other._data->is_big) {
        if (is_copy) {
            _data = other._data;
        } else {
            _old_data = other._data;
            _data.swap(_old_data);
            is_copy = true;
        }
    } else {
        data_copy();
        _data->ensure_capacity(other._data->size);
        std::copy(other._data->union_data.small_data, other._data->union_data.small_data + other._data->size,
                  _data->union_data.small_data);
    }
    return *this;
}

uint32_t my_vector::back() const {
    return operator[](_data->size - 1);
}

uint32_t &my_vector::back() {
    return operator[](_data->size - 1);
}

bool my_vector::empty() const {
    return size() == 0;
}
