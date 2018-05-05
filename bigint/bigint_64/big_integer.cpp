//
// Created by Vladislav Kalugin on 12.04.2018.
//

#include <string>
#include "big_integer.h"
#include "gtest/gtest.h"

typedef __uint128_t u128;
typedef __int128_t i128;

big_integer::big_integer()
        : sign(true), data(0) {}

big_integer::big_integer(big_integer const &other) = default;

big_integer::big_integer(int a) : sign(a >= 0) {
    data.assign(1, static_cast<uint64_t>(abs((long long int) a)));
}

void big_integer::add_uint64_t(uint64_t const x) {
    u128 result = data[0] + static_cast<u128>(x);
    data[0] = static_cast<uint64_t>(result);
    uint64_t carry = static_cast<uint64_t>(result >> std::numeric_limits<uint64_t>::digits);
    uint64_t position = 1;
    while (carry != 0) {
        if (position == data.size()) {
            result = static_cast<u128>(carry);
            data.push_back(static_cast<uint64_t>(result));
        } else {
            result = static_cast<u128>(data[position]) + carry;
            data[position] = static_cast<uint64_t>(result);
        }
        carry = static_cast<uint64_t>(result >> std::numeric_limits<uint64_t>::digits);
        position++;
    }
}

void big_integer::mul_uint64_t(uint64_t const x) {
    u128 mul = static_cast<uint64_t>(x);
    u128 carry = 0;
    u128 result = 0;
    for (size_t i = 0; i < data.size() || carry > 0; i++) {
        if (i == data.size()) {
            result = static_cast<u128>(carry);
            data.push_back(static_cast<uint64_t>(result));
        } else {
            result = mul * data[i] + carry;
            data[i] = static_cast<uint64_t>(result);
        }
        carry = static_cast<uint64_t>(result >> std::numeric_limits<uint64_t>::digits);
    }
}

big_integer::big_integer(std::string const &str) {
    sign = true;
    data.assign(1, 0);
    size_t position = 0;
    if (str[position] == '-') {
        sign = false;
        position++;
    }
    for (; position != str.length(); position++) {
        uint64_t digit = static_cast<uint64_t>(str[position] - '0');
        mul_uint64_t(10);
        add_uint64_t(digit);
    }
}

big_integer::~big_integer() = default;

big_integer &big_integer::operator=(big_integer const &other) = default;

bool big_integer::is_zero() const {
    return (data.empty()) || (data.size() == 1 && data[0] == 0);
}

int big_integer::compare_by_abs(big_integer const &other) const {
    if (this->is_zero() && other.is_zero()) { return 0; }
    if (this->data.size() > other.data.size()) { return 1; }
    if (this->data.size() < other.data.size()) { return -1; }
    for (size_t i = this->data.size(); i > 0; i--) {
        if (this->data[i - 1] > other.data[i - 1]) { return 1; }
        if (this->data[i - 1] < other.data[i - 1]) { return -1; }
    }
    return 0;
}

int big_integer::compare(big_integer const &other) const {
    if (this->sign != other.sign) {
        if (this->sign) {
            return 1;
        } else {
            return -1;
        }
    }
    int ret = this->compare_by_abs(other);
    if (this->sign && other.sign) {
        return ret;
    } else {
        return -ret;
    }
}

bool operator==(big_integer const &left, big_integer const &right) {
    return left.compare(right) == 0;
}

bool operator!=(big_integer const &left, big_integer const &right) {
    return left.compare(right) != 0;
}

bool operator>(big_integer const &left, big_integer const &right) {
    return left.compare(right) == 1;
}

bool operator>=(big_integer const &left, big_integer const &right) {
    return left.compare(right) >= 0;
}

bool operator<(big_integer const &left, big_integer const &right) {
    return left.compare(right) == -1;
}

bool operator<=(big_integer const &left, big_integer const &right) {
    return left.compare(right) <= 0;
}


void big_integer::clean() {
    while (!data.empty() && data.back() == 0) {
        data.pop_back();
    }
    if (data.empty()) {
        sign = true;
    }
}


void big_integer::add_unsigned(big_integer const &rhs) {
    uint64_t carry = 0;
    u128 result = 0;
    size_t max_range = std::max(this->data.size(), rhs.data.size());
    for (size_t i = 0; i < max_range || carry > 0; i++) {
        if (i == this->data.size()) {
            if (i < rhs.data.size()) {
                result = static_cast<u128>(carry) + rhs.data[i];
            } else {
                result = static_cast<u128>(carry);
            }
            this->data.push_back(static_cast<uint64_t>(result));
        } else {
            if (i < rhs.data.size()) {
                result = static_cast<u128>(carry) + this->data[i] + rhs.data[i];
            } else {
                result = static_cast<u128>(carry) + this->data[i];
            }
            this->data[i] = static_cast<uint64_t>(result);
        }
        carry = static_cast<uint64_t>(result >> std::numeric_limits<uint64_t>::digits);
    }
    this->clean();
}

void big_integer::sub_uint64_t(uint64_t const x) {
    uint64_t sub = x;
    i128 result = 0;
    bool loan = false;
    result = static_cast<i128>(data[0]) - sub;
    if (result >= 0) {
        data[0] = static_cast<uint64_t>(result);
    } else {
        result += (static_cast<u128>(std::numeric_limits<uint64_t>::max()) + 1);
        data[0] = static_cast<uint64_t>(result);
        loan = true;
    }
    for (size_t i = 1; i < data.size() && loan; i++) {
        if (data[i]) {
            data[i]--;
            loan = false;
        } else {
            data[i] = std::numeric_limits<uint64_t>::max() - 1;
        }
    }
}

void big_integer::sub_unsigned(big_integer const &rhs) {
    bool loan = false;
    i128 result = 0;
    i128 minuend = 0;
    i128 sub = 0;
    for (size_t i = 0; i != this->data.size(); i++) {
        minuend = this->data[i];
        if (i < rhs.data.size()) {
            sub = rhs.data[i];
        } else if (loan) {
            sub = 0;
        } else {
            break;
        }

        if (loan) {
            minuend -= 1;
            loan = false;
        }
        result = minuend - sub;
        if (result < 0) {
            result += (static_cast<u128>(std::numeric_limits<uint64_t>::max()) + 1);
            loan = true;
        }
        this->data[i] = static_cast<uint64_t>(result);
    }
}


big_integer big_integer::operator+() const {
    return *this;
}

big_integer big_integer::operator-() const {
    if (*this == 0) {
        return *this;
    }
    big_integer ret(*this);
    ret.sign = !ret.sign;
    return ret;
}

big_integer &big_integer::operator+=(big_integer const &rhs) {
    if (rhs.is_zero()) {
        return *this;
    }
    if (this->is_zero()) {
        return *this = rhs;
    }
    if (this->sign == rhs.sign) {
        if (rhs.data.size() == 1) {
            this->add_uint64_t(rhs.data.back());
        } else {
            this->add_unsigned(rhs);
        }
    } else {
        int compare = this->compare_by_abs(rhs);
        if (compare == 0) {
            return *this = 0;
        } else if (compare == 1)
            if (rhs.data.size() == 1) {
                this->sub_uint64_t(rhs.data.back());
            } else {
                this->sub_unsigned(rhs);
            }
        else {
            big_integer minuend(rhs);
            minuend.sub_unsigned(*this);
            *this = minuend;
            this->sign = rhs.sign;
        }
    }
    this->clean();
    return *this;
}

big_integer operator+(big_integer left, const big_integer &right) {
    left += right;
    return left;
}

big_integer &big_integer::operator++() {
    if (this->sign) {
        this->add_uint64_t(1);
    } else {
        this->sub_uint64_t(1);
    }
    return *this;

}

big_integer big_integer::operator++(int) {
    big_integer ret(*this);
    ++ret;
    return ret;
}


big_integer &big_integer::operator-=(big_integer const &rhs) {
    *this += -rhs;
    this->clean();
    return *this;
}

big_integer operator-(big_integer left, const big_integer &right) {
    left -= right;
    return left;
}

big_integer &big_integer::operator--() {
    if (!this->sign) {
        this->add_uint64_t(1);
    } else {
        this->sub_uint64_t(1);
    }
    return *this;
}

big_integer big_integer::operator--(int) {
    big_integer ret(*this);
    --ret;
    return ret;
}

big_integer &big_integer::operator<<=(int shift) {
    uint64_t insert = static_cast<uint64_t>(shift) / std::numeric_limits<uint64_t>::digits;
    data.insert(data.begin(), insert, 0);
    uint64_t shl = static_cast<uint64_t>(shift) % std::numeric_limits<uint64_t>::digits;
    if (shl != 0) {
        for (size_t i = data.size() - 1; i != 0; i--) {
            data[i] = ((data[i] << shl) | (data[i - 1] >> (std::numeric_limits<uint64_t>::digits - shl)));
        }
        data[0] <<= shl;
    }
    clean();
    return *this;
}

big_integer operator<<(big_integer number, int shift) {
    number <<= shift;
    return number;
}

big_integer &big_integer::operator>>=(int shift) {
    uint64_t del = static_cast<uint64_t>(shift) / std::numeric_limits<uint64_t>::digits;
    if (del > data.size()) {
        return *this = 0;
    }
    data.erase(data.begin(), data.begin() + del);
    uint64_t shr = static_cast<uint64_t>(shift) % std::numeric_limits<uint64_t>::digits;
    if (shr != 0) {
        for (size_t i = 0; i != data.size() - 1; i++) {
            data[i] = ((data[i] >> shr) | (data[i + 1] << (std::numeric_limits<uint64_t>::digits - shr)));
        }
        data[data.size() - 1] >>= shr;
    }
    clean();
    if (*this < 0) {
        add_uint64_t(1);
    }
    return *this;
}

big_integer operator>>(big_integer number, int shift) {
    number >>= shift;
    return number;
}


big_integer big_integer::mul_uint64_t_return(uint64_t const x) const {
    big_integer ret(*this);
    ret.mul_uint64_t(x);
    ret.clean();
    return ret;
}


big_integer &big_integer::operator*=(big_integer const &rhs) {
    this->sign = this->sign == rhs.sign;
    big_integer result(this->mul_uint64_t_return(rhs.data[0]));
    for (size_t i = 1; i != rhs.data.size(); ++i) {
        result += this->mul_uint64_t_return(rhs.data[i]) << (std::numeric_limits<uint64_t>::digits * i);
    }
    return *this = result;
}

big_integer operator*(big_integer left, const big_integer &right) {
    left *= right;
    return left;
}

uint64_t big_integer::div_uint64_t(uint64_t const x) {
    uint64_t carry = 0;
    u128 result = 0;
    for (size_t i = data.size(); i > 0; i--) {
        result = data[i - 1] + carry * (static_cast<u128>(std::numeric_limits<uint64_t>::max()) + 1);
        data[i - 1] = static_cast<uint64_t>(result / x);
        carry = static_cast<uint64_t>(result % x);
    }
    clean();
    return carry;
}

big_integer &big_integer::operator/=(big_integer const &rhs) {
    bool flag_sign = this->sign == rhs.sign;
    int compare = this->compare_by_abs(rhs);
    if (compare == 0) {
        sign = flag_sign;
        *this = 1;
        return *this;
    }
    if (compare == -1) {
        sign = true;
        *this = 0;
        return *this;
    }
    if (rhs.data.size() == 1) {
        this->div_uint64_t(rhs.data.back());
        this->sign = flag_sign;
        return *this;
    }
    big_integer divider(rhs);
    this->sign = divider.sign = true;
    uint64_t norma = std::numeric_limits<uint64_t>::max() / (divider.data.back() + 1);
    this->mul_uint64_t(norma);
    divider.mul_uint64_t(norma);
    size_t m = this->data.size() - divider.data.size();
    size_t n = divider.data.size();
    big_integer res;
    if (*this >= divider << (std::numeric_limits<uint64_t>::digits * m)) {
        *this -= divider << (std::numeric_limits<uint64_t>::digits * m);
        res.data.resize(m + 1);
        res.data.back() = 1;
    } else {
        res.data.resize(m);
    }
    u128 result = 0;
    for (size_t i = m; i != 0; i--) {
        if (n + i - 1 < this->data.size()) {
            result = ((static_cast<u128>(this->data[n + i - 1])
                    << std::numeric_limits<uint64_t>::digits) +
                      this->data[n + i - 2]) / static_cast<u128>(divider.data.back());
        } else {
            result = static_cast<u128>(this->data[n + i - 2] / divider.data.back());
        }
        res.data[i - 1] = std::min(static_cast<uint64_t>(result), std::numeric_limits<uint64_t>::max());
        *this -= divider.mul_uint64_t_return(res.data[i - 1]) << (std::numeric_limits<uint64_t>::digits * (i - 1));
        while (*this < 0) {
            res.data[i - 1]--;
            *this += divider << (std::numeric_limits<uint64_t>::digits * (i - 1));
        }
    }
    res.sign = flag_sign;
    res.clean();
    return *this = res;
}

big_integer operator/(big_integer left, const big_integer &right) {
    left /= right;
    return left;
}

big_integer &big_integer::operator%=(const big_integer &rhs) {
    return *this -= (*this / rhs) * rhs;
}

big_integer operator%(big_integer left, const big_integer &right) {
    left %= right;
    return left;
}


void big_integer::code() {
    if (!sign) {
        for (size_t i = 0; i != data.size(); ++i)
            data[i] = ~data[i];
        add_uint64_t(1);
    }
}

void big_integer::decode() {
    if (!sign) {
        sub_uint64_t(1);
        for (size_t i = 0; i != data.size(); ++i)
            data[i] = ~data[i];
    }
}

big_integer &big_integer::operator&=(const big_integer &rhs) {
    big_integer that(rhs);
    if (that.data.size() > this->data.size()) {
        this->data.insert(this->data.end(), that.data.size() - this->data.size(), 0);
    }
    this->code();
    that.code();
    for (size_t i = 0; i != that.data.size(); i++) {
        this->data[i] &= that.data[i];
    }
    this->sign = this->sign || that.sign;
    this->decode();
    this->clean();
    return *this;
}

big_integer operator&(big_integer left, const big_integer &right) {
    left &= right;
    return left;
}

big_integer &big_integer::operator|=(const big_integer &rhs) {
    big_integer that(rhs);
    if (that.data.size() > this->data.size()) {
        this->data.insert(this->data.end(), that.data.size() - this->data.size(), 0);
    }
    this->code();
    that.code();
    for (size_t i = 0; i != that.data.size(); i++) {
        this->data[i] |= that.data[i];
    }
    for (size_t i = that.data.size(); i < this->data.size(); i++) {
        this->data[i] |= 0;
    }
    this->sign = this->sign && that.sign;
    this->decode();
    this->clean();
    return *this;
}

big_integer operator|(big_integer left, const big_integer &right) {
    left |= right;
    return left;
}

big_integer &big_integer::operator^=(const big_integer &rhs) {
    big_integer that(rhs);
    if (that.data.size() > this->data.size()) {
        this->data.insert(this->data.end(), that.data.size() - this->data.size(), 0);
    }
    this->code();
    that.code();
    for (size_t i = 0; i != that.data.size(); i++) {
        this->data[i] ^= that.data[i];
    }
    for (size_t i = that.data.size(); i < this->data.size(); i++) {
        this->data[i] ^= 0;
    }
    this->sign = !(this->sign ^ that.sign);
    this->decode();
    this->clean();
    return *this;
}

big_integer operator^(big_integer left, const big_integer &right) {
    left ^= right;
    return left;
}

big_integer big_integer::operator~() const {
    big_integer ret(*this);
    ret.add_uint64_t(1);
    ret.sign = !ret.sign;
    return ret;
}

std::string to_string(big_integer const &a) {
    if (a.is_zero()) {
        return "0";
    }
    std::string res;
    big_integer tmp(a);
    while (tmp != 0) {
        uint64_t digit = tmp.div_uint64_t(10);
        res.push_back(static_cast<char>(digit + '0'));
    }
    if (!a.sign) {
        res.push_back('-');
    }
    std::reverse(res.begin(), res.end());
    return res;
}

std::ostream &operator<<(std::ostream &os, big_integer const &a) {
    os << to_string(a);
    return os;
}

#undef u128
#undef i128
