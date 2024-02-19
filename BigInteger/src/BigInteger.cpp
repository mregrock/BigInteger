//
// Created by Егор Кулин on 27.01.2024.
//
#include "../include/BigInteger.h"

namespace big_num {
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
            if (chunks_sum >= MAX_CHUNK) {
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

    //TODO: Fix Karatsuba multiplication
    /*BigInteger KaratsubaMultiplication(const BigInteger &first, const BigInteger &second) {
        if (first.integral_size_ < 2 || second.integral_size_ < 2) {
            return first * second;
        }
        int n = std::max(first.integral_size_, second.integral_size_);
        int n_2 = n / 2;
        BigInteger high1, low1, high2, low2;
        high1.SetSizeInChunks(n_2);
        low1.SetSizeInChunks(n_2);
        high2.SetSizeInChunks(n_2);
        low2.SetSizeInChunks(n_2);
        for (int i = 0; i < n_2; i++) {
            high1.SetChunk(i, first.GetChunk(i));
            low1.SetChunk(i, first.GetChunk(i + n_2));
            high2.SetChunk(i, second.GetChunk(i));
            low2.SetChunk(i, second.GetChunk(i + n_2));
        }
        BigInteger z0 = KaratsubaMultiplication(low1, low2);
        BigInteger z1 = KaratsubaMultiplication(low1 + high1, low2 + high2);
        BigInteger z2 = KaratsubaMultiplication(high1, high2);
        return z2 * (1_bi << (2 * n_2)) + (z1 - z2 - z0) * (1_bi << n_2) + z0;
    }*/


    BigInteger BigInteger::operator*=(const BigInteger &other) {
        return (*this = *this * other);
    }

    BigInteger operator/(const BigInteger &left_num, const BigInteger &right_num) {
        if (right_num == 0_bi){
            throw std::overflow_error("Divide by zero exception");
        }
        BigInteger res;
        BigInteger mult = 0_bi;
        int left_num_size = static_cast<int>(left_num.integral_size_);
        std::string bin_res;
        for (int i = left_num_size - 1; i >= 0; i--) {
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
        int chunk_shift = shift / CHUNK_SIZE;
        int bit_shift = shift % CHUNK_SIZE;
        BigInteger result;
        result.SetSizeInChunks(num.integral_size_ + chunk_shift + 1);
        for (int i = 0; i < num.integral_size_; i++) {
            result.integral_[i + chunk_shift] = (num.integral_[i] % ((1ull) << (CHUNK_SIZE - bit_shift))) << bit_shift;
            result.integral_[i + chunk_shift + 1] += (num.integral_[i] / (1ull << (CHUNK_SIZE - bit_shift)));
        }
        result.TrimLeadingZeroes();
        return result;
    }


    BigInteger BigInteger::Pow(const BigInteger &num, int times) {
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