//
// Created by Егор Кулин on 27.01.2024.
//

#ifndef BIGINT_BIGINTEGER_H
#define BIGINT_BIGINTEGER_H


#include <string>
#include <iostream>

class BigInteger {
    int precision_;
    int base_;
    int a;
public:
    BigInteger();

    BigInteger(std::string);

    ~BigInteger();

    friend const BigInteger operator+(BigInteger, const BigInteger &);

    friend std::ostream &operator<<(std::ostream &, const BigInteger &);
};


#endif //BIGINT_BIGINTEGER_H
