//
// Created by Егор Кулин on 15.02.2024.
//
#include "BigFloat.h"

namespace big_num {
    BigFloat::BigFloat(std::string str_num) {
        int index = static_cast<int>(str_num.find('.'));
        std::string next_str;
        int count_bit = 0;
        std::string fraction_str = str_num.substr(index + 1);
        str_num = str_num.substr(0, index);
        int chunk_num = precision_;
        for (int i = 0; i < precision_; i++) {
            this->AddChunk(0);
        }
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
        if (index != -1) {
            for (chunk_num = this->precision_ - 1; chunk_num >= 0; chunk_num--) {
                for (int num_bit = CHUNK_SIZE - 1; num_bit >= 0; num_bit--) {
                    next_str = str_ops::MultByTwo(fraction_str);
                    if (next_str.size() != fraction_str.size()) {
                        next_str.erase(next_str.begin());
                        fraction_str = next_str;
                        //std::cout << "1";
                        this->integral_[chunk_num] += (1ull << num_bit);
                    } else {
                        //std::cout << "0";
                    }
                    fraction_str = next_str;
                }
            }
        }
        this->integral_size_ = this->integral_.size();
        this->fraction_size_ = this->fraction_.size();
    }

    BigFloat::BigFloat() {
        this->integral_size_ = 0;
        this->fraction_size_ = 0;
        this->exp_ = 0;
        this->is_positive_ = true;
    }

    BigFloat::BigFloat(double value) {
        std::string str_value = std::to_string(value);
        *this = BigFloat(str_value);
    }

    BigFloat::BigFloat(const BigFloat &other) {
        this->integral_ = other.GetIntegral();
        this->integral_size_ = other.GetSizeInChunks();
        this->is_positive_ = other.is_positive_;
        this->exp_ = other.exp_;
    }

    BigFloat::~BigFloat() {
        this->integral_.clear();
        this->fraction_.clear();
    }


    BigFloat BigFloat::CreateFromBinary(const std::string &bin_str) {
        BigFloat result;
        result.AddChunk(0);
        int bin_str_size = static_cast<int>(bin_str.size());
        int count_bit = 0;
        int num_chunk = 0;
        int last_index = 0;
        if (bin_str[0] == '-') {
            result.is_positive_ = false;
            last_index = 1;
        }
        for (int i = bin_str_size - 1; i >= last_index; i--) {
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
}