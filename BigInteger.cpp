//
// Created by Егор Кулин on 27.01.2024.
//

#include "BigInteger.h"


BigInteger::BigInteger() {
    this->fraction_.assign(precision_, 0);
    this->integral_.assign(base_, 0);
    this->integral_size_ = 0;
    this->fraction_size_ = 0;
}

chunk_t BigInteger::GetChunk(const int &i) const {
    if (i >= this->integral_size_) {
        return 0;
    }
    return this->integral_[i];
}


void BigInteger::AddChunk(const chunk_t &num) {
    this->integral_.push_back(num);
    this->integral_size_++;
}

const std::vector<chunk_t> &BigInteger::GetIntegral() const {
    return this->integral_;
}

BigInteger::BigInteger(std::string str_num) {
    int index = static_cast<int>(str_num.find('.'));
    std::string next_str;
    int count_bit = 0;
    int chunk_num = 0;
    this->integral_.push_back(0);
    while (str_num != "1" && str_num != "0") {
        next_str.clear();
        std::size_t str_num_size = str_num.size();
        long long num = 0;
        bool is_not_leading_zeroes = false;
        for (int i = 0; i < str_num_size; i++) {
            num = num * 10 + (str_num[i] - '0');
            if (num / 2 != 0) {
                is_not_leading_zeroes = true;
            }
            if (is_not_leading_zeroes) {
                next_str.push_back(static_cast<char>(num / 2 + '0'));
            }
            num = num % 2;
        }
        this->integral_[chunk_num] += (num << count_bit);
        count_bit++;
        if (count_bit == CHUNK_SIZE) {
            count_bit = 0;
            chunk_num++;
            this->integral_.push_back(0);
        }
        str_num = next_str;
    }
    this->integral_[chunk_num] += ((std::stoll(next_str)) << count_bit);
    this->integral_size_ = this->integral_.size();
    this->fraction_size_ = this->fraction_.size();
}

BigInteger::~BigInteger() {
    this->integral_.clear();
    this->fraction_.clear();
}


std::string BigInteger::ToString() {
    std::string string_decimal;
    for (int i = 0; i < this->integral_size_; i++) {
        string_decimal.push_back(0);
    }
    return string_decimal;
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

BigInteger operator*(const BigInteger &first, const BigInteger &second) {
    const std::vector<chunk_t> &first_integral = first.GetIntegral();
    const std::vector<chunk_t> &second_integral = second.GetIntegral();
    const std::size_t &first_integral_size = first_integral.size();
    const std::size_t &second_integral_size = second_integral.size();
    BigInteger res;
    res.SetSizeInChunks(first_integral.size() + second_integral.size() + 1);
    for (auto i = 0; i < first_integral_size; ++i) {
        for (auto j = 0; j < second_integral_size; ++j) {
            chunk_t chunk_res = first_integral[i] * second_integral[j];
            chunk_t chunk_set_res = res.GetChunk(i + j) + chunk_res;
            res.SetChunk(i + j, chunk_set_res % MAX_CHUNK);
            res.SetChunk(i + j + 1, res.GetChunk(i + j + 1) + (chunk_set_res) / MAX_CHUNK);
            //res.SetChunk
        }
    }
    auto &res_integral = const_cast<std::vector<chunk_t> &>(res.GetIntegral());
    while (*res_integral.rbegin() == 0) {
        res_integral.pop_back();
    }
    return res;
}

BigInteger operator+(const BigInteger &first, const BigInteger &second) {
    std::size_t new_size = (first.integral_size_ > second.integral_size_ ? first.integral_size_
                                                                         : second.integral_size_);
    BigInteger result;
    chunk_t remainder = 0;
    for (int i = 0; i < new_size; i++) {
        chunk_t chunks_sum = first.GetChunk(i) + second.GetChunk(i) + remainder;
        remainder = 0;
        if (chunks_sum > MAX_CHUNK) {
            chunks_sum = chunks_sum % MAX_CHUNK;
            remainder = 1;
        }
        result.AddChunk(chunks_sum);
    }
    if (remainder != 0) {
        result.AddChunk(remainder);
    }
    return result;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &number) {
    const std::vector<chunk_t> &integral = number.GetIntegral();
    std::size_t integral_size = integral.size();
    for (int i = 0; i < integral_size; i++) {

    }
}

BigInteger operator ""_bi(const char *s) {
    return BigInteger{s};
}




