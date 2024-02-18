//
// Created by Егор Кулин on 27.01.2024.
//

#ifndef BIGINT_BigFloat_H
#define BIGINT_BigFloat_H


#include <string>
#include <iostream>
#include <vector>
#include "BigInteger.h"

#define CHUNK_SIZE 32
#define PRECISION 512
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
    class BigFloat {
        int precision_ = PRECISION / CHUNK_SIZE;
        int exp_;
        bool is_positive_ = true;
        std::vector <chunk_t> integral_;
        std::vector <chunk_t> fraction_;
        std::size_t integral_size_;
        std::size_t fraction_size_;

    public:
        BigFloat();

        explicit BigFloat(std::string);

        ~BigFloat();

        BigFloat(const BigFloat &);

        BigFloat operator+() const;

        BigFloat operator-() const;

        BigFloat &operator=(const BigFloat &);

        friend BigFloat operator+(const BigFloat &, const BigFloat &);

        BigFloat operator+=(const BigFloat &);

        friend BigFloat operator-(const BigFloat &, const BigFloat &);

        BigFloat operator-=(const BigFloat &);

        friend BigFloat operator*(const BigFloat &, const BigFloat &);

        friend BigFloat KaratsubaMultiplication(const BigFloat &, const BigFloat &);

        BigFloat operator*=(const BigFloat &);

        friend BigFloat operator/(const BigFloat &, const BigFloat &);

        BigFloat operator/=(const BigFloat &);

        friend bool operator==(const BigFloat &, const BigFloat &);

        friend bool operator<(const BigFloat &, const BigFloat &);

        friend bool operator>(const BigFloat &, const BigFloat &);

        friend bool operator<=(const BigFloat &, const BigFloat &);

        friend bool operator>=(const BigFloat &, const BigFloat &);

        friend BigFloat operator>>(const BigFloat &, int);

        friend BigFloat operator<<(const BigFloat &, int);

        friend std::ostream &operator<<(std::ostream &, const BigFloat &);

        friend std::istream &operator>>(std::istream &, BigFloat &);

        [[nodiscard]] std::string ToStringIntegral() const;

        [[nodiscard]] std::string ToStringFractional() const;

        [[nodiscard]] std::string ToString() const;

        [[nodiscard]] std::string ToBinaryString() const;

        [[nodiscard]] static BigFloat CreateFromBinary(const std::string &);

        BigFloat Abs() const;

        [[nodiscard]] const std::vector <chunk_t> &GetIntegral() const;

        [[nodiscard]] chunk_t GetChunk(const int &) const;

        [[nodiscard]] bool IsPositive() const;

        void SetChunk(const int &, const chunk_t &);

        void SetSizeInChunks(const std::size_t &);

        [[nodiscard]] BigFloat Pow(const BigFloat &, const int &times) const;

        [[nodiscard]] std::size_t GetSizeInChunks() const;

        void PopChunk();

        void TrimLeadingZeroes();

        void TrimFunc();

        void AddChunk(const chunk_t &);

        [[nodiscard]] big_num::BigInteger ToBigInt() const;

        [[nodiscard]] big_num::BigInteger ToBigIntNarrow() const;

    };

    void Swap(BigFloat &, BigFloat &);
}

big_num::BigFloat operator ""_bf(const char *);


#endif //BIGINT_BigFloat_H
