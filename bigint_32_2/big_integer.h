//
// Created by Vladislav Kalugin on 12.04.2018.
//

#ifndef BIGINTEGER_BIG_INTEGER_H
#define BIGINTEGER_BIG_INTEGER_H

#include <string>
#include <limits>
#include <vector>
#include "my_vector.h"


struct big_integer {
private:
    bool sign;
    my_vector data;

    void mul_uint32_t(uint32_t);

    void add_uint32_t(uint32_t);

    void sub_uint32_t(uint32_t);

    bool is_zero() const;

    int compare_by_abs(big_integer const &) const;

    int compare(big_integer const &) const;

    void remove_lead_zeros();

    void add_unsigned(big_integer const &);

    void sub_unsigned(big_integer const &);

    void code();

    void decode();

    big_integer mul_uint32_t_return(uint32_t x) const;

    uint32_t div_uint32_t(uint32_t x);

public:
    big_integer();

    big_integer(big_integer const &other);

    big_integer(int a);

    big_integer(std::string const &str);

    ~big_integer();

    big_integer &operator=(big_integer const &other);

    big_integer &operator+=(big_integer const &rhs);

    big_integer &operator-=(big_integer const &rhs);

    big_integer &operator*=(big_integer const &rhs);

    big_integer &operator/=(big_integer const &rhs);

    big_integer &operator%=(big_integer const &rhs);

    big_integer &operator&=(big_integer const &rhs);

    big_integer &operator|=(big_integer const &rhs);

    big_integer &operator^=(big_integer const &rhs);

    big_integer &operator<<=(int rhs);

    big_integer &operator>>=(int rhs);

    big_integer operator+() const;

    big_integer operator-() const;

    big_integer operator~() const;

    big_integer &operator++();

    big_integer operator++(int);

    big_integer &operator--();

    big_integer operator--(int);

    friend bool operator==(big_integer const &a, big_integer const &b);

    friend bool operator!=(big_integer const &a, big_integer const &b);

    friend bool operator<(big_integer const &a, big_integer const &b);

    friend bool operator>(big_integer const &a, big_integer const &b);

    friend bool operator<=(big_integer const &a, big_integer const &b);

    friend bool operator>=(big_integer const &a, big_integer const &b);

    friend std::string to_string(big_integer const &a);
};

big_integer operator+(big_integer a, big_integer const &b);

big_integer operator-(big_integer a, big_integer const &b);

big_integer operator*(big_integer a, big_integer const &b);

big_integer operator/(big_integer a, big_integer const &b);

big_integer operator%(big_integer a, big_integer const &b);

big_integer operator&(big_integer a, big_integer const &b);

big_integer operator|(big_integer a, big_integer const &b);

big_integer operator^(big_integer a, big_integer const &b);

big_integer operator<<(big_integer a, int b);

big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const &a, big_integer const &b);

bool operator!=(big_integer const &a, big_integer const &b);

bool operator<(big_integer const &a, big_integer const &b);

bool operator>(big_integer const &a, big_integer const &b);

bool operator<=(big_integer const &a, big_integer const &b);

bool operator>=(big_integer const &a, big_integer const &b);

std::string to_string(big_integer const &a);

std::ostream &operator<<(std::ostream &s, big_integer const &a);

#endif //BIGINTEGER_BIG_INTEGER_H
