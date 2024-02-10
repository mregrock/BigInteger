#include <iostream>
#include "BigInteger.h"

int main() {
    BigInteger a = 894239429349_bi;
    BigInteger b = 9931293999999999_bi;
    BigInteger c = a * b;
    std::cout << c.GetChunk(0) << " " << c.GetChunk(1) << " " << c.GetChunk(2) << " " << c.GetChunk(3) << "\n";
    std::cout << c.GetSizeInChunks() << "\n";
    std::cout << c;
    return 0;
}
