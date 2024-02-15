//
// Created by Егор Кулин on 15.02.2024.
//

#include <gtest/gtest.h>
#include "BigInteger.h"
TEST(Addition, SimpleAddition){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = 9876543210_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "11111111100");
}

TEST(Addition, AdditionWithCarry){
    big_num::BigInteger a = 9999999999_bi;
    big_num::BigInteger b = 1_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "10000000000");
}

TEST(Addition, AdditionWithNegative){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = -1234567890_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "0");
}

TEST(Addition, AdditionWithNegativeAndCarry){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = -1234567891_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "-1");
}
TEST(Addition, AdditionWithDifferentSize){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = 12345678901234567890_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "12345678901235802480");
}

TEST(Addition, AdditionWithDifferentSizeAndCarry){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = 12345678901234567890_bi;
    big_num::BigInteger c = b + a;
    ASSERT_EQ(c.ToString(), "12345678901235802480");
}

TEST(Addition, AdditionWithDifferentSizeAndNegative){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = -12345678901234567890_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "-12345678901233333300");
}

TEST(Addition, AdditionWithDifferentSizeAndNegativeAndCarry){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = -12345678901234567891_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "-12345678901233333301");
}

TEST(Addition, AdditionWithDifferentSizeAndNegativeAndCarry2){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = -12345678901234567891_bi;
    big_num::BigInteger c = b + a;
    ASSERT_EQ(c.ToString(), "-12345678901233333301");
}

TEST(Addition, NegativeAddition){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = -9876543210_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "-11111111100");
}

TEST(Addition, NegativeAdditionWithCarry){
    big_num::BigInteger a = -9999999999_bi;
    big_num::BigInteger b = -1_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "-10000000000");
}

TEST(Addition, NegativeAdditionWithNegative){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = 1234567890_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "0");
}

TEST(Addition, NegativeAdditionWithNegativeAndCarry){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = 1234567891_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "1");
}

TEST(Addition, NegativeAdditionWithDifferentSize){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = 12345678901234567890_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "12345678901233333300");
}

TEST(Addition, NegativeAdditionWithDifferentSizeAndCarry){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = 12345678901234567890_bi;
    big_num::BigInteger c = b + a;
    ASSERT_EQ(c.ToString(), "12345678901233333300");
}

TEST(Addition, NegativeAdditionWithDifferentSizeAndNegative){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = -12345678901234567890_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "-12345678901235802480");
}

TEST(Addition, NegativeAdditionWithDifferentSizeAndNegativeAndCarry){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = -12345678901234567891_bi;
    big_num::BigInteger c = a + b;
    ASSERT_EQ(c.ToString(), "-12345678901235802481");
}

TEST(Addition, NegativeAdditionWithDifferentSizeAndNegativeAndCarry2){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = -12345678901234567891_bi;
    big_num::BigInteger c = b + a;
    ASSERT_EQ(c.ToString(), "-12345678901235802481");
}