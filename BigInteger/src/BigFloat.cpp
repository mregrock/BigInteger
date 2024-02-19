//
// Created by Егор Кулин on 27.01.2024.
//

#include "../include/BigFloat.h"
#include "../include/BigInteger.h"
namespace big_num {
    BigFloat &BigFloat::operator=(const BigFloat &other) {
        this->integral_ = other.integral_;
        this->integral_size_ = other.integral_size_;
        this->is_positive_ = other.is_positive_;
        this->exp_ = other.exp_;
        return *this;
    }

    BigFloat operator+(const BigFloat &first, const BigFloat &second) {
        if (first.is_positive_ ^ second.is_positive_) {
            if (first.is_positive_) {
                return first - second.Abs();
            }
            return second - first.Abs();
        }
        std::size_t new_size = (first.integral_size_ > second.integral_size_ ? first.integral_size_
                                                                             : second.integral_size_);
        BigFloat result;
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

    BigFloat BigFloat::operator+=(const BigFloat &other) {
        return (*this = *this + other);
    }

    BigFloat operator-(const BigFloat &first_num, const BigFloat &second_num) {
        BigFloat first(first_num);
        BigFloat second(second_num);
        BigFloat result;
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

    BigFloat BigFloat::operator+() const {
        return *this;
    }

    BigFloat BigFloat::operator-() const {
        BigFloat result = *this;
        result.is_positive_ = !result.is_positive_;
        return result;
    }

    BigFloat operator*(const BigFloat &first, const BigFloat &second) {
        BigFloat res;
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


    BigFloat BigFloat::operator*=(const BigFloat &other) {
        return (*this = *this * other);
    }

    BigFloat operator/(const BigFloat &left_num, const BigFloat &right_num) {
        BigFloat res;
        std::string bin_res;
        big_num::BigInteger left_num_new = left_num.ToBigIntNarrow();
        big_num::BigInteger right_num_new = right_num.ToBigIntNarrow();
        left_num_new = left_num_new << (left_num.precision_ * CHUNK_SIZE);
        big_num::BigInteger res_new = left_num_new / right_num_new;
        bin_res = res_new.ToBinaryString();
        res = BigFloat::CreateFromBinary(bin_res);
        if (left_num.is_positive_ ^ right_num.is_positive_) {
            res.is_positive_ = false;
        }
        return res;
    }

    BigFloat BigFloat::operator/=(const BigFloat &other) {
        return (*this = *this / other);
    }

    bool operator==(const BigFloat &left_num, const BigFloat &right_num) {
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

    bool operator<(const BigFloat &left_num, const BigFloat &right_num) {
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

    bool operator<=(const BigFloat &left_num, const BigFloat &right_num) {
        return ((left_num < right_num) || (left_num == right_num));
    }

    bool operator>(const BigFloat &left_num, const BigFloat &right_num) {
        return !(left_num <= right_num);
    }

    bool operator>=(const BigFloat &left_num, const BigFloat &right_num) {
        return !(left_num < right_num);
    }

    BigFloat operator>>(const BigFloat &num, int shift) {
        std::string bin_num = num.ToBinaryString();
        std::string shifted_num = str_ops::operator>>(bin_num, shift);
        return BigFloat::CreateFromBinary(shifted_num);
    }

    BigFloat operator<<(const BigFloat &num, int shift) {
        std::string bin_num = num.ToBinaryString();
        std::string shifted_num = str_ops::operator<<(bin_num, shift);
        return BigFloat::CreateFromBinary(shifted_num);
    }


    BigFloat BigFloat::Pow(const BigFloat &num, const int &times) const {
        BigFloat result = 1_bf;
        for (int i = 0; i < times; i++) {
            result *= num;
        }
        return result;
    }

    std::istream &operator>>(std::istream &in, BigFloat &num) {
        std::string str_num;
        in >> str_num;
        num = BigFloat{str_num};
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const BigFloat &number) {
        out << number.ToString();
        return out;
    }
}

big_num::BigFloat operator ""_bf(const char *s) {
    return big_num::BigFloat{s};
}