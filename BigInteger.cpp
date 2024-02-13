//
// Created by Егор Кулин on 27.01.2024.
//

#include "BigInteger.h"

namespace {
    std::string MultByTwo(const std::string &str_num) {
        std::string result;
        int str_size = static_cast<int>(str_num.size());
        int remainder = 0;
        for (int i = str_size - 1; i >= 0; i--) {
            int digit_result = ((str_num[i] - '0') * 2);
            result.push_back(static_cast<char>(digit_result % 10 + remainder + '0'));
            remainder = digit_result / 10;
        }
        if (remainder != 0) {
            result.push_back('1');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::string Inc(const std::string &str_num) {
        std::string result;
        int str_size = static_cast<int>(str_num.size());
        int remainder = 1;
        for (int i = str_size - 1; i >= 0; i--) {
            int digit_result = ((str_num[i] - '0') + remainder);
            result.push_back(static_cast<char>(digit_result % 10 + '0'));
            remainder = digit_result / 10;
        }
        if (remainder != 0) {
            result.push_back('1');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
}

namespace big_num {
    BigInteger::BigInteger() {
        this->fraction_.assign(precision_, 0);
        this->integral_.assign(base_, 0);
        this->integral_size_ = 0;
        this->fraction_size_ = 0;
    }

    BigInteger::~BigInteger() {
        this->integral_.clear();
        this->fraction_.clear();
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

    void BigInteger::PopChunk() {
        this->integral_.pop_back();
        this->integral_size_--;
    }

    void BigInteger::TrimLeadingZeroes() {
        while (*this->integral_.rbegin() == 0 && this->integral_size_ > 1) {
            this->PopChunk();
        }
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

    std::string BigInteger::ToString() const {
        std::string result = "0";
        int integral_size = static_cast<int>(this->integral_size_);
        bool not_zero = false;
        for (int i = integral_size - 1; i >= 0; i--) {
            for (int j = CHUNK_SIZE - 1; j >= 0; j--) {
                if (!not_zero) {
                    if (((1ull << j) & this->integral_[i])) {
                        not_zero = true;
                    }
                }
                if (not_zero) {
                    result = MultByTwo(result);
                    if (((1ull << j) & this->integral_[i])) {
                        result = Inc(result);
                    }
                }
            }
        }
        return result;
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

    BigInteger BigInteger::operator=(const BigInteger &other) {
        this->integral_ = other.GetIntegral();
        this->integral_size_ = other.GetSizeInChunks();
        return *this;
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
        res.TrimLeadingZeroes();
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

    BigInteger BigInteger::operator+=(const BigInteger &other) {
        return (*this = *this + other);
    }

    BigInteger BigInteger::operator*=(const BigInteger &other) {
        return (*this = *this * other);
    }

    BigInteger BigInteger::pow(const BigInteger &num, const int &times) const {
        BigInteger result = 1_bi;
        for (int i = 0; i < times; i++) {
            result *= num;
        }
        return result;
    }

    std::ostream &operator<<(std::ostream &out, const BigInteger &number) {
        out << number.ToString();
        return out;
    }

    BigInteger::BigInteger(
            const BigInteger &other) {
        this->integral_ = other.GetIntegral();
        this->integral_size_ = other.GetSizeInChunks();

    }

    std::size_t BigInteger::GetSizeInChunks() const {
        return this->integral_size_;
    }

}
big_num::BigInteger operator ""_bi(const char *s) {
    return big_num::BigInteger{s};
}