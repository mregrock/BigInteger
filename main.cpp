#include <iostream>
#include "BigInteger/include/BigInteger.h"
#include <ctime>

int main() {
    big_num::BigInteger a = 894239429349_bi;
    big_num::BigInteger b = 9931293999999999_bi;
    clock_t t1 = clock();
    big_num::BigInteger c = a * b;
    std::cout << KaratsubaMultiplication(a, b) << "\n";
    std::cout << c.GetSizeInChunks() << "\n";
    std::cout << c << "\n";
    std::cout << 9223372036854775808_bi / 576460752303423488_bi << "\n";
    std::cout << c / a << std::endl;
    big_num::BigInteger c_2 = 80954679257146711123123123123123123123760570651_bi;
    big_num::BigInteger first{"0"};
    big_num::BigInteger second = 0_bi;
    clock_t t2 = clock();
    big_num::BigInteger c_5 = 10000007237584534950000000000000000000000000000000000000000000000000000000000_bi;
    std::string c_binary = c_5.ToBinaryString();
    clock_t t3 = clock();
    std::cout << c_5 + c << "\n";
    std::cout << (c + c_5) - c << "\n";
    std::cout << -(c_5) - c << "\n";
    std::cout << -(c + c_5) + c_5 << "\n";
    std::cout << (c - c_5) / c << "\n";
    std::cout << (18446744073709551616_bi) - (1_bi) << "\n";
    clock_t t4 = clock();
    std::cout << (-1_bi < 0_bi) << "\n";
    std::cout << 1000.0 * (t2 - t1) / CLOCKS_PER_SEC << "\n";
    //std::cout << 1000.0 * (t3 - t1) / CLOCKS_PER_SEC << "\n";
    std::cout << 1000.0 * (t4 - t1) / CLOCKS_PER_SEC;;
    return 0;
}
