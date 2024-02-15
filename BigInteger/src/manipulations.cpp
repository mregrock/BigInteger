//
// Created by Егор Кулин on 15.02.2024.
//
#include "BigInteger.h"

namespace big_num {
    chunk_t BigInteger::GetChunk(const int &i) const {
        if (i >= this->integral_size_) {
            return 0;
        }
        return this->integral_[i];
    }

    std::size_t BigInteger::GetSizeInChunks() const {
        return this->integral_size_;
    }

    void BigInteger::AddChunk(const chunk_t &num) {
        this->integral_.push_back(num);
        this->integral_size_++;
    }

    void BigInteger::PopChunk() {
        this->integral_.pop_back();
        this->integral_size_--;
    }

    const std::vector <chunk_t> &BigInteger::GetIntegral() const {
        return this->integral_;
    }

    bool BigInteger::IsPositive() const {
        return this->is_positive_;
    }

    void Swap(BigInteger &first, BigInteger &second) {
        BigInteger third = first;
        first = second;
        second = third;
    }

    BigInteger BigInteger::Abs() const {
        BigInteger result = *this;
        result.is_positive_ = true;
        return result;
    }

    void BigInteger::TrimLeadingZeroes() {
        while (*this->integral_.rbegin() == 0 && this->integral_size_ > 1) {
            this->PopChunk();
        }
    }

    void BigInteger::SetSizeInChunks(const std::size_t &size) {
        this->integral_.assign(size, 0);
        this->integral_size_ = size;
    }

    void BigInteger::SetChunk(const int &index, const chunk_t &num) {
        while (this->integral_size_ <= index) {
            this->AddChunk(0);
        }
        this->integral_[index] = num;
    }


}