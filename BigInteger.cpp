//
// Created by Егор Кулин on 27.01.2024.
//

#include "BigInteger.h"

namespace str_ops {
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

    std::string operator>>(std::string str_num, int shift) {
        int shift_with_size = (shift < str_num.size() ? shift : static_cast<int>(str_num.size()));
        str_num.erase(str_num.end() - shift_with_size, str_num.end());
        if (str_num.empty()) {
            str_num.push_back('0');
        }
        return str_num;
    }

    std::string operator<<(std::string str_num, int shift) {
        for (int i = 0; i < shift; i++) {
            str_num.push_back('0');
        }
        return str_num;
    }

}

namespace big_num {
    BigInteger::BigInteger() {
        this->integral_size_ = 0;
        this->fraction_size_ = 0;
        this->is_positive_ = true;
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
        this->AddChunk(0);
        if (str_num[0] == '-') {
            this->is_positive_ = false;
            str_num.erase(str_num.begin());
        }
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
        this->integral_[chunk_num] += ((std::stoll(str_num)) << count_bit);
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
                    result = str_ops::MultByTwo(result);
                    if (((1ull << j) & this->integral_[i])) {
                        result = str_ops::Inc(result);
                    }
                }
            }
        }
        if (!this->is_positive_ && result != "0") {
            result = "-" + result;
        }
        return result;
    }

    std::string BigInteger::ToBinaryString() const {
        std::string result;
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
                    result.push_back(static_cast<char>((((1ull << j) & this->integral_[i]) >> j) + '0'));
                }
            }
        }
        return result;
    }

    BigInteger BigInteger::CreateFromBinary(std::string &bin_str) {
        BigInteger result;
        result.AddChunk(0);
        int bin_str_size = static_cast<int>(bin_str.size());
        int count_bit = 0;
        int num_chunk = 0;
        for (int i = bin_str_size - 1; i >= 0; i--) {
            result.integral_[num_chunk] += (static_cast<long long>(bin_str[i] - '0') << count_bit);
            count_bit++;
            if (count_bit == 32) {
                count_bit = 0;
                num_chunk++;
                result.AddChunk(0);
            }
        }
        result.TrimLeadingZeroes();
        return result;
    }

    void swap(BigInteger &first, BigInteger &second) {
        BigInteger third = first;
        first = second;
        second = third;
    }

    BigInteger BigInteger::Abs() const {
        BigInteger result = *this;
        result.is_positive_ = true;
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

    BigInteger &BigInteger::operator=(const BigInteger &other) {
        this->integral_ = other.integral_;
        this->integral_size_ = other.integral_size_;
        this->is_positive_ = other.is_positive_;
        return *this;
    }

    BigInteger operator+(const BigInteger &first, const BigInteger &second) {
        if (first.is_positive_ ^ second.is_positive_) {
            if (first.is_positive_) {
                return first - second.Abs();
            }
            return second - first.Abs();
        }
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
        result.TrimLeadingZeroes();
        if (!first.is_positive_ && !second.is_positive_) {
            result.is_positive_ = false;
        }
        return result;
    }

    BigInteger BigInteger::operator+=(const BigInteger &other) {
        return (*this = *this + other);
    }

    BigInteger operator-(const BigInteger &first_num, const BigInteger &second_num) {
        BigInteger first(first_num);
        BigInteger second(second_num);
        BigInteger result;
        if (first_num.is_positive_ ^ second_num.is_positive_) {
            if (first_num.is_positive_) {
                return first_num + (-second_num);
            }
            return -(-first_num + second_num);
        }
        if (first < second && first.is_positive_ && second.is_positive_) {
            big_num::swap(first, second);
            result.is_positive_ = false;
        }
        std::size_t new_size = (first.integral_size_ > second.integral_size_ ? first.integral_size_
                                                                             : second.integral_size_);
        chunk_t remainder = 0;
        for (int i = 0; i < new_size; i++) {
            chunk_t chunk_res;
            if (first.GetChunk(i) < second.GetChunk(i) + remainder) {
                chunk_res = first.GetChunk(i) + ((1ull << 32) - second.GetChunk(i) - remainder);
                remainder = 1;
            } else {
                chunk_res = first.GetChunk(i) - second.GetChunk(i) - remainder;
                remainder = 0;
            }
            result.AddChunk(chunk_res);
        }
        result.TrimLeadingZeroes();
        return result;
    }

    BigInteger BigInteger::operator+() const {
        return *this;
    }

    BigInteger BigInteger::operator-() const {
        BigInteger result = *this;
        result.is_positive_ = !result.is_positive_;
        return result;
    }

    BigInteger operator*(const BigInteger &first, const BigInteger &second) {
        BigInteger res;
        res.SetSizeInChunks(first.integral_size_ + second.integral_size_ + 1);
        for (auto i = 0; i < first.integral_size_; ++i) {
            for (auto j = 0; j < second.integral_size_; ++j) {
                chunk_t chunk_res = first.integral_[i] * second.integral_[j];
                chunk_t chunk_set_res = res.GetChunk(i + j) + chunk_res;
                res.SetChunk(i + j, chunk_set_res % MAX_CHUNK);
                res.SetChunk(i + j + 1, res.GetChunk(i + j + 1) + (chunk_set_res) / MAX_CHUNK);
            }
        }
        res.TrimLeadingZeroes();
        if (first.is_positive_ ^ second.is_positive_) {
            res.is_positive_ = false;
        }
        return res;
    }

    BigInteger KaratsubaMultiplication(const BigInteger &first, const BigInteger &second) {
        if (first.integral_size_ < 2 || second.integral_size_ < 2) {
            return first * second;
        }
        int n = std::max(first.integral_size_, second.integral_size_);
        int m = n / 2;
        BigInteger first_low;
        BigInteger first_high;
        BigInteger second_low;
        BigInteger second_high;
        for (int i = 0; i < m; i++) {
            first_low.AddChunk(first.GetChunk(i));
            second_low.AddChunk(second.GetChunk(i));
        }
        for (int i = m; i < n; i++) {
            first_high.AddChunk(first.GetChunk(i));
            second_high.AddChunk(second.GetChunk(i));
        }
        BigInteger z0 = KaratsubaMultiplication(first_low, second_low);
        BigInteger z1 = KaratsubaMultiplication(first_high, second_high);
        BigInteger z2 = KaratsubaMultiplication(first_low + first_high, second_low + second_high);
        return z1 * (1_bi << (2 * m)) + (z2 - z1 - z0) * (1_bi << m) + z0;
    }


    BigInteger BigInteger::operator*=(const BigInteger &other) {
        return (*this = *this * other);
    }

    BigInteger operator/(const BigInteger &left_num, const BigInteger &right_num) {
        BigInteger res;
        BigInteger mult = 0_bi;
        int left_num_size = static_cast<int>(left_num.integral_size_);
        std::string bin_res;
        for (int i = 1; i >= 0; i--) {
            for (int bit = CHUNK_SIZE - 1; bit >= 0; bit--) {
                int shift = (CHUNK_SIZE) * (i) + bit;
                BigInteger add = (right_num << (shift));
                if (mult + add <= left_num) {
                    mult = mult + add;
                    bin_res.push_back('1');
                } else {
                    bin_res.push_back('0');
                }
            }
        }
        res = BigInteger::CreateFromBinary(bin_res);
        if (left_num.is_positive_ ^ right_num.is_positive_) {
            res.is_positive_ = false;
        }
        return res;
    }

    BigInteger BigInteger::operator/=(const BigInteger &other) {
        return (*this = *this / other);
    }

    bool operator==(const BigInteger &left_num, const BigInteger &right_num) {
        std::size_t size_left = left_num.integral_size_;
        std::size_t size_right = right_num.integral_size_;
        if (left_num.is_positive_ != right_num.is_positive_) {
            if (!(left_num.integral_size_ == 1 && left_num.integral_[0] == 0 && right_num.integral_size_ == 1 &&
                  right_num.integral_[0] == 0)) {
                return false;
            }
        }
        if (size_left != size_right) {
            return false;
        }
        for (int i = 0; i < size_left; i++) {
            if (left_num.integral_[i] != right_num.integral_[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<(const BigInteger &left_num, const BigInteger &right_num) {
        int size_left = static_cast<int>(left_num.GetSizeInChunks());
        std::size_t size_right = right_num.GetSizeInChunks();
        if (left_num.is_positive_ != right_num.is_positive_) {
            if (!(left_num.integral_size_ == 1 && left_num.integral_[0] == 0 && right_num.integral_size_ == 1 &&
                  right_num.integral_[0] == 0)) {
                return false;
            }
        }
        if (!left_num.is_positive_ && !right_num.is_positive_) {
            return (-right_num < -left_num);
        }
        if (size_left < size_right) {
            return true;
        }
        if (size_left > size_right) {
            return false;
        }
        for (int i = size_left - 1; i >= 0; i--) {
            if (left_num.GetChunk(i) < right_num.GetChunk(i)) {
                return true;
            }
            if (left_num.GetChunk(i) > right_num.GetChunk(i)) {
                return false;
            }
        }
        return false;
    }

    bool operator<=(const BigInteger &left_num, const BigInteger &right_num) {
        return ((left_num < right_num) || (left_num == right_num));
    }

    bool operator>(const BigInteger &left_num, const BigInteger &right_num) {
        return !(left_num <= right_num);
    }

    bool operator>=(const BigInteger &left_num, const BigInteger &right_num) {
        return !(left_num < right_num);
    }

    BigInteger operator>>(const BigInteger &num, int shift) {
        std::string bin_num = num.ToBinaryString();
        std::string shifted_num = str_ops::operator>>(bin_num, shift);
        return BigInteger::CreateFromBinary(shifted_num);
    }

    BigInteger operator<<(const BigInteger &num, int shift) {
        std::string bin_num = num.ToBinaryString();
        std::string shifted_num = str_ops::operator<<(bin_num, shift);
        return BigInteger::CreateFromBinary(shifted_num);
    }


    BigInteger BigInteger::pow(const BigInteger &num, const int &times) const {
        BigInteger result = 1_bi;
        for (int i = 0; i < times; i++) {
            result *= num;
        }
        return result;
    }


    BigInteger::BigInteger(const BigInteger &other) {
        this->integral_ = other.GetIntegral();
        this->integral_size_ = other.GetSizeInChunks();
        this->is_positive_ = other.is_positive_;
    }

    std::size_t BigInteger::GetSizeInChunks() const {
        return this->integral_size_;
    }

    std::istream &operator>>(std::istream &in, BigInteger &num) {
        std::string str_num;
        in >> str_num;
        num = BigInteger{str_num};
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const BigInteger &number) {
        out << number.ToString();
        return out;
    }
}

big_num::BigInteger operator ""_bi(const char *s) {
    return big_num::BigInteger{s};
}
