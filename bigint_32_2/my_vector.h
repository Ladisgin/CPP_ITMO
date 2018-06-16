//
// Created by Vladislav Kalugin on 10/06/2018.
//

#ifndef BIGINT_MY_VECTOR_H
#define BIGINT_MY_VECTOR_H

#include <string>
#include <limits>
#include <memory>

class my_vector {
private:
    static const size_t SMALL_SIZE = 2;
    union {
        uint32_t small_data[SMALL_SIZE];
        uint32_t *big_data;
    } union_data;
    std::shared_ptr<uint32_t *> _data;
    size_t data_capacity;
    size_t data_size;
    bool is_big;

    void reserve(size_t sz);

    void copy_check();

public:
    void resize(size_t sz);

    void resize(size_t sz, uint32_t val);

    my_vector(size_t sz, uint32_t val);

    my_vector(size_t sz);

    my_vector();

    my_vector(my_vector const &other);

    size_t size() const;

    uint32_t back() const;

    uint32_t &back();

    void push_back(uint32_t val);

    uint32_t operator[](size_t pos) const;

    uint32_t &operator[](size_t pos);

    void pop_back();

    bool empty();

    my_vector &operator=(my_vector const &other);
};


#endif //BIGINT_MY_VECTOR_H
