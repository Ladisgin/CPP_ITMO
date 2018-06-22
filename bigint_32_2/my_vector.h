//
// Created by Vladislav Kalugin on 10/06/2018.
//

#ifndef BIGINT_MY_VECTOR_H
#define BIGINT_MY_VECTOR_H

#include <string>
#include <limits>
#include <memory>

struct data_struct {
    static const size_t SMALL_SIZE = 4;
    union {
        uint32_t small_data[SMALL_SIZE];
        uint32_t *big_data;
    } union_data;

    size_t size;
    size_t capacity;
    bool is_big;

    data_struct();

    ~data_struct();

    void ensure_capacity(size_t new_size);
};


class my_vector {
private:
    std::shared_ptr<data_struct> _data;
    bool is_copy;
    std::shared_ptr<data_struct> _old_data;
public:
    void data_copy();

    void data_without_copy();

    my_vector();

    my_vector(my_vector const &other);

    my_vector(size_t sz);

    my_vector(size_t sz, uint32_t val);

    void resize(size_t sz);

    void resize(size_t sz, uint32_t val);

    size_t size() const;

    void push_back(uint32_t val);

    uint32_t operator[](size_t pos) const;

    uint32_t &operator[](size_t pos);

    void pop_back();

    my_vector &operator=(my_vector const &other);

    uint32_t back() const;

    uint32_t &back();

    bool empty() const;
};


#endif //BIGINT_MY_VECTOR_H