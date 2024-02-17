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

    std::string BigInteger::ToString() const {;
        std::string result;
        std::string integral_part = this->ToStringIntegral();
        std::string fraction_part = this->ToStringFractional();
        if (fraction_part != "0" && integral_part != "0") {
            result = integral_part + "." + fraction_part;
        } else if (fraction_part == "0") {
            result = integral_part;
        } else {
            result = "0." + fraction_part;
        }
        return result;
    }

    std::string BigInteger::ToStringIntegral() const {
        std::string result = "0";
        int integral_size = static_cast<int>(this->integral_size_);
        bool not_zero = false;
        for (int i = integral_size - 1; i >= this->precision_; i--) {
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

    std::string BigInteger::ToStringFractional() const {
        bool is_null = true;
        for (int i = 0; i < this->precision_; i++) {
            if (this->integral_[i] != 0) {
                is_null = false;
                break;
            }
        }
        if (is_null) {
            return "0";
        }
        BigInteger fraction = 1_bi;
        BigInteger five_power = 5_bi;
        BigInteger ten_power = 1_bi;
        bool is_leading_nulls = true;
        std::string leading_nulls;
        for (int i = this->precision_ - 1; i >= 0; i--) {
            for (int j = CHUNK_SIZE - 1; j >= 0; j--) {
                fraction = fraction * 10_bi;
                if (((1ull << j) & this->integral_[i])) {
                    fraction += five_power;
                }
                five_power *= 5_bi;
            }
        }
        std::string second_res = fraction.ToStringIntegral();
        second_res.erase(second_res.begin());
        while (*second_res.rbegin() == '0'){
            second_res.pop_back();
        }
        return second_res;
    }
}