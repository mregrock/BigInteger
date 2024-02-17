//
// Created by Егор Кулин on 15.02.2024.
//
#include <gtest/gtest.h>
#include "BigInteger.h"
TEST(Fractional, DivideFractional){
    big_num::BigInteger a = 2.25_bi;
    big_num::BigInteger b = 1.5_bi;
    big_num::BigInteger c = a / b;
    ASSERT_EQ(c.ToString(), "1.5");
}
TEST(Fractional, CreateFractional){
    big_num::BigInteger a = 568_bi;
    big_num::BigInteger b = 541_bi;
    big_num::BigInteger c = a / b;
    ASSERT_EQ(c.ToString(), "1.25");
}