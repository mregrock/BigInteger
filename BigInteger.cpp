//
// Created by Егор Кулин on 27.01.2024.
//

#include "BigInteger.h"

BigInteger::BigInteger() {
    this->fraction_.assign(precision_, 0);
    this->integral_.assign(base_, 0);
}

BigInteger::BigInteger(const std::string &str_num) {
    int index = static_cast<int>(str_num.find('.'));
    std::size_t str_size = str_num.size();
    std::size_t integral_size = index;
    this->integral_.assign(integral_size, 0);
    for (int i = 0; i < integral_size; i++) {
        this->integral_[integral_size - i] = str_num[i] - '0';
    }
    for (int i = index + 1; i < str_size; i++) {
        this->fraction_[i - index - 1] = str_num[i] - '0';
    }
}

BigInteger::~BigInteger() {
    this->integral_.clear();
    this->fraction_.clear();
}

std::ostream &operator<<(std::ostream &out, const BigInteger &number){
    out << number.a;
    return out;
}

BigInteger operator+(const BigInteger &first, const BigInteger &second) {
    BigInteger c;
    for (int i = 0; i < n; i++) {

    }
}

BigInteger operator ""_bi(const char *s) {
    return BigInteger{s};
}




