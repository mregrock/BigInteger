//
// Created by Егор Кулин on 15.02.2024.
//
#include <gtest/gtest.h>
#include "BigInteger.h"

TEST(Multiplication, SimpleMultiplication){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = 9876543210_bi;
    big_num::BigInteger c = a * b;
    ASSERT_EQ(c.ToString(), "12193263111263526900");
}

TEST(Multiplication, MultiplicationWithCarry){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = 1234567890_bi;
    big_num::BigInteger c = a * b;
    ASSERT_EQ(c.ToString(), "1524157875019052100");
}

TEST(Multiplication, MultiplicationWithNegative){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = -1234567890_bi;
    big_num::BigInteger c = a * b;
    ASSERT_EQ(c.ToString(), "-1524157875019052100");
}
