//
// Created by Егор Кулин on 15.02.2024.
//
#include "BigInteger.h"
#include <algorithm>
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