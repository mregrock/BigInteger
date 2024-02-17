//
// Created by Егор Кулин on 27.01.2024.
//

#include "../include/BigInteger.h"

namespace big_num {
    BigInteger &BigInteger::operator=(const BigInteger &other) {
        this->integral_ = other.integral_;
        this->integral_size_ = other.integral_size_;
        this->is_positive_ = other.is_positive_;
        this->exp_ = other.exp_;
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
            big_num::Swap(first, second);
            result.is_positive_ = false;
        }
        if (!first.is_positive_ && !second.is_positive_) {
            return (-second - (-first));
        }
        std::size_t new_size = (first.integral_size_ > second.integral_size_ ? first.integral_size_
                                                                             : second.integral_size_);
        chunk_t remainder = 0;
        for (int i = 0; i < new_size; i++) {
            chunk_t chunk_res;
            if (first.GetChunk(i) < second.GetChunk(i) + remainder) {
                chunk_res = first.GetChunk(i) + ((1ull << CHUNK_SIZE) - second.GetChunk(i) - remainder);
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
        int cnt_last = 0;
        while (cnt_last != res.precision_) {
            res.integral_.erase(res.integral_.begin());
            res.integral_size_--;
            cnt_last++;
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
        std::string bin_res;
        BigInteger left_num_new = left_num << PRECISION;
        int left_num_size = static_cast<int>(left_num_new.integral_size_);
        for (int i = left_num_size - 1; i >= 0; i--) {
            for (int bit = CHUNK_SIZE - 1; bit >= 0; bit--) {
                int shift = (CHUNK_SIZE) * (i - left_num.precision_) + bit;
                BigInteger add = (right_num << (shift));
                if (mult + add <= left_num_new) {
                    mult = mult + add;
                    bin_res.push_back('1');
                } else {
                    bin_res.push_back('0');
                }
            }
        }
        /*for (int i = left_num.precision_ - 1; i >= 0; i--){
            for (int bit = CHUNK_SIZE - 1; bit >= 0; bit--){
                int shift = (CHUNK_SIZE) * (i - left_num.precision_) + bit;
                shift = -shift;
                BigInteger add = (right_num >> (shift));
                if (mult + add <= left_num){
                    mult = mult + add;
                    bin_res.push_back('1');
                }
                else{
                    bin_res.push_back('0');
                }
            }
        }*/
        bin_res = str_ops::operator>>(bin_res, PRECISION);
        std::cout << bin_res << std::endl;
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


    BigInteger BigInteger::Pow(const BigInteger &num, const int &times) const {
        BigInteger result = 1_bi;
        for (int i = 0; i < times; i++) {
            result *= num;
        }
        return result;
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