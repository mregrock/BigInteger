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
    std::string next_str;
    int count_bit = 0;
    int chunk_num = 0;
    while (next_str != "0"){
        std::size_t str_num_size = str_num.size();
        int num = 0;
        for (int i = 0; i < str_num_size; i++){
            num = num * 10 + (str_num[i] - '0');
            if (num > 2){
                next_str.push_back(static_cast<char>(num / 2));
                num = num % 2;
            }
        }
        this->integral_[chunk_num] += (num << count_bit);
        count_bit += 1;
        if (count_bit == 32){
            count_bit = 0;
            chunk_num++;
        }
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




