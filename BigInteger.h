//
// Created by Егор Кулин on 27.01.2024.
//

#ifndef BIGINT_BIGINTEGER_H
#define BIGINT_BIGINTEGER_H


#include <string>
#include <iostream>
#include <vector>
#include <bitset>

#define CHUNK_SIZE 32
typedef unsigned long long chunk_t;
#define MAX_CHUNK (1ull << CHUNK_SIZE)

class BigInteger {
    int precision_ = 100;
    int base_ = 0;
    std::vector<chunk_t> integral_;
    std::vector<chunk_t> fraction_;
    std::size_t integral_size_;
    std::size_t fraction_size_;
public:
    BigInteger();

    explicit BigInteger(std::string);

    ~BigInteger();

    friend BigInteger operator+(const BigInteger &, const BigInteger &);


    friend BigInteger operator*(const BigInteger &, const BigInteger &);

    friend std::ostream &operator<<(std::ostream &, const BigInteger &);

    std::string ToString();

    const std::vector<chunk_t> &GetIntegral() const;

    chunk_t GetChunk(const int &) const;

    void SetChunk(const int &, const chunk_t &);

    void SetSizeInChunks(const std::size_t &);

    std::size_t GetSizeInChunks() const;

    void AddChunk(const chunk_t &);

};

BigInteger operator ""_bi(const char *);


#endif //BIGINT_BIGINTEGER_H
