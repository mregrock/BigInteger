#include <iostream>
#include "BigInteger/include/BigInteger.h"
#include <ctime>

int main() {
    big_num::BigInteger a = 894239429349_bi;
    big_num::BigInteger b = 9931293999999999_bi;
    clock_t t1 = clock();
    big_num::BigInteger c = a * b;
    std::cout << c.GetSizeInChunks() << "\n";
    std::cout << c << "\n";
    std::cout << 9223372036854775808_bi / 576460752303423488_bi << "\n";
    std::cout << c / a << std::endl;
    big_num::BigInteger c_2 = 80954679257146711123123123123123123123760570651_bi;
    big_num::BigInteger first{"0"};
    big_num::BigInteger second = 0_bi;
    return 0;
}
