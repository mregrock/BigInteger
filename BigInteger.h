//
// Created by Егор Кулин on 27.01.2024.
//

#ifndef BIGINT_BIGINTEGER_H
#define BIGINT_BIGINTEGER_H


#include <string>
#include <iostream>
#include <vector>
#include <bitset>
#define CHUNK_SIZE (1 << 32)
#define chunk_t int

class BigInteger {
    int precision_ = 100;
    int base_ = 0;
    std::vector<chunk_t> integral_;
    std::vector<chunk_t> fraction_;

public:
    BigInteger();

    BigInteger(const std::string &);

    ~BigInteger();

    friend BigInteger operator+(const BigInteger &, const BigInteger &);



    friend std::ostream &operator<<(std::ostream &, const BigInteger &);

};

BigInteger operator ""_bi(const char *);


#endif //BIGINT_BIGINTEGER_H
