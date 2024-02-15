//
// Created by Егор Кулин on 15.02.2024.
//
#include "BigInteger.h"

namespace big_num {
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
}