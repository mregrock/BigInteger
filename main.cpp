#include <iostream>
#include "BigInteger.h"

int main() {
    BigInteger a = 899123499123999_bi;
    BigInteger b = 151231239123123_bi;
    BigInteger c = a * b;
    std::cout << c.GetChunk(0) << " " << c.GetChunk(1) << " " << c.GetChunk(2) << " " << c.GetChunk(3);
    return 0;
}
