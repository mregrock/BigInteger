#include <iostream>
#include "BigInteger/include/BigInteger.h"
#include <ctime>

int main() {
    big_num::BigInteger a = 568_bi;
    big_num::BigInteger first = a * big_num::BigInteger::Pow(2_bi, 512);
    big_num::BigInteger second = a;
    for (int i = 0; i < 512; i++){
        second += second;
    }
    big_num::BigInteger third = (a << 512);
    std::cout << first << std::endl;
    std::cout << second << std::endl;
    std::cout << third << std::endl;

    return 0;
}
