//
// Created by Егор Кулин on 27.01.2024.
//

#include "BigInteger.h"


BigInteger::BigInteger() {
    this->a = 0;
}

BigInteger::BigInteger(const std::string string_number) {
    this->a = stoi(string_number);
}

BigInteger::~BigInteger() {

}

std::ostream &operator<<(std::ostream &out, const BigInteger &number) {
    out << number.a;
    return out;
}

const BigInteger operator+(BigInteger first, const BigInteger &second) {
    BigInteger c;
    c.a = first.a + second.a;
    return c;
}