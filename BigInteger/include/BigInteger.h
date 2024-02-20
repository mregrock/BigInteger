//
// Created by Егор Кулин on 27.01.2024.
//

#ifndef BIGINT_BIGINTEGER_H
#define BIGINT_BIGINTEGER_H


#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

#define CHUNK_SIZE 32
typedef unsigned long long chunk_t;
#define MAX_CHUNK (1ull << CHUNK_SIZE)

namespace str_ops {
    std::string MultByTwo(const std::string &str_num);

    std::string Inc(const std::string &str_num);

    [[nodiscard]] static std::vector <chunk_t> StringToNumeric(std::string);

    [[nodiscard]] static std::string NumericToString(const std::vector <chunk_t> &);

    std::string operator>>(std::string str_num, int shift);

    std::string operator<<(std::string str_num, int shift);
}

namespace big_num {
    class BigInteger {
        bool is_positive_ = true;
        std::vector <chunk_t> integral_;
        std::vector <chunk_t> fraction_;
        std::size_t integral_size_;
        std::size_t fraction_size_;

    public:
        BigInteger();

        explicit BigInteger(std::string);

        BigInteger (long long);

        ~BigInteger();

        BigInteger(const BigInteger &);

        BigInteger operator+() const;

        BigInteger operator-() const;

        BigInteger &operator=(const BigInteger &);

        friend BigInteger operator+(const BigInteger &, const BigInteger &);

        BigInteger& operator+=(const BigInteger &);

        friend BigInteger operator-(const BigInteger &, const BigInteger &);

        BigInteger& operator-=(const BigInteger &);

        friend BigInteger operator*(const BigInteger &, const BigInteger &);

        friend BigInteger KaratsubaMultiplication(const BigInteger &, const BigInteger &);

        BigInteger& operator*=(const BigInteger &);

        friend BigInteger operator/(const BigInteger &, const BigInteger &);

        BigInteger& operator/=(const BigInteger &);

        friend bool operator==(const BigInteger &, const BigInteger &);

        friend bool operator<(const BigInteger &, const BigInteger &);

        friend bool operator>(const BigInteger &, const BigInteger &);

        friend bool operator<=(const BigInteger &, const BigInteger &);

        friend bool operator>=(const BigInteger &, const BigInteger &);

        friend BigInteger operator>>(const BigInteger &, int);

        friend BigInteger operator<<(const BigInteger &, int);

        friend std::ostream &operator<<(std::ostream &, const BigInteger &);

        friend std::istream &operator>>(std::istream &, BigInteger &);

        [[nodiscard]] std::string ToString() const;

        [[nodiscard]] std::string ToBinaryString() const;

        [[nodiscard]] static BigInteger CreateFromBinary(const std::string &);

        BigInteger Abs() const;

        [[nodiscard]] const std::vector <chunk_t> &GetIntegral() const;

        [[nodiscard]] chunk_t GetChunk(const int &) const;

        [[nodiscard]] bool IsPositive() const;

        void SetChunk(const int &, const chunk_t &);

        void SetSizeInChunks(const std::size_t &);

        [[nodiscard]] static BigInteger Pow(const BigInteger &, int times);

        [[nodiscard]] std::size_t GetSizeInChunks() const;

        void PopChunk();

        void TrimLeadingZeroes();

        void TrimFunc();

        void AddChunk(const chunk_t &);

    };

    void Swap(BigInteger &, BigInteger &);
}

big_num::BigInteger operator ""_bi(const char *);


#endif //BIGINT_BIGINTEGER_H
