//
// Created by Егор Кулин on 15.02.2024.
//

#include "BigInteger.h"

namespace big_num {
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
}