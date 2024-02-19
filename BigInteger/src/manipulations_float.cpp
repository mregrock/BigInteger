//
// Created by Егор Кулин on 15.02.2024.
//
#include "BigFloat.h"

namespace big_num {
    chunk_t BigFloat::GetChunk(const int &i) const {
        if (i >= this->integral_size_) {
            return 0;
        }
        return this->integral_[i];
    }

    std::size_t BigFloat::GetSizeInChunks() const {
        return this->integral_size_;
    }

    void BigFloat::AddChunk(const chunk_t &num) {
        this->integral_.push_back(num);
        this->integral_size_++;
    }

    void BigFloat::PopChunk() {
        this->integral_.pop_back();
        this->integral_size_--;
    }

    const std::vector <chunk_t> &BigFloat::GetIntegral() const {
        return this->integral_;
    }

    bool BigFloat::IsPositive() const {
        return this->is_positive_;
    }

    void Swap(BigFloat &first, BigFloat &second) {
        BigFloat third = first;
        first = second;
        second = third;
    }

    BigFloat BigFloat::Abs() const {
        BigFloat result = *this;
        result.is_positive_ = true;
        return result;
    }

    void BigFloat::TrimLeadingZeroes() {
        while (*this->integral_.rbegin() == 0 && this->integral_size_ > this->precision_) {
            this->PopChunk();
        }
    }

    void BigFloat::SetSizeInChunks(const std::size_t &size) {
        this->integral_.assign(size, 0);
        this->integral_size_ = size;
    }

    void BigFloat::SetChunk(const int &index, const chunk_t &num) {
        while (this->integral_size_ <= index) {
            this->AddChunk(0);
        }
        this->integral_[index] = num;
    }

    void BigFloat::SetPrecision(int precision) {
        while (precision > this->precision_){
            this->AddChunk(0);
            precision--;
        }
        while(precision < this->precision_){
            this->PopChunk();
            this->precision_--;
        }
    }

    BigInteger BigFloat::ToBigInt() const {
        BigInteger result;
        for (int i = this->precision_; i < this->integral_size_; i++) {
            result.AddChunk(this->integral_[i]);
        }
        if (!this->is_positive_) {
            result = -result;
        }
        return result;
    }

    BigInteger BigFloat::ToBigIntNarrow() const {
        BigInteger result;
        for (int i = 0; i < this->integral_size_; i++) {
            result.AddChunk(this->integral_[i]);
        }
        if (!this->is_positive_) {
            result = -result;
        }
        result.TrimLeadingZeroes();
        return result;
    }

}