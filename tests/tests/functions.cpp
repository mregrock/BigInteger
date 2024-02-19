//
// Created by Егор Кулин on 20.02.2024.
//
#include "BigInteger.h"
#include "BigFloat.h"
#include <gtest/gtest.h>

TEST(Functions, Pow){
    big_num::BigInteger a = 2_bi;
    big_num::BigInteger c = big_num::BigInteger::Pow(a, 100);
    ASSERT_EQ(c.ToString(), "1267650600228229401496703205376");
}

TEST(Functions, PowWithNegative){
    big_num::BigInteger a = -2_bi;
    big_num::BigInteger c = big_num::BigInteger::Pow(a, 101);
    ASSERT_EQ(c.ToString(), "-2535301200456458802993406410752");
}

TEST(Functions, PowWithZero){
    big_num::BigInteger a = 0_bi;
    big_num::BigInteger c = big_num::BigInteger::Pow(a, 100);
    ASSERT_EQ(c.ToString(), "0");
}

TEST(Functions, BitShift){
    big_num::BigInteger a = 1_bi;
    big_num::BigInteger c = a << 100;
    ASSERT_EQ(c.ToString(), "1267650600228229401496703205376");
}

TEST(Functions, BitShiftWithZero){
    big_num::BigInteger a = 0_bi;
    big_num::BigInteger c = a << 100;
    ASSERT_EQ(c.ToString(), "0");
}

TEST(Functions, BitShiftRight){
    big_num::BigInteger a = 1267650600228229401496703205376_bi;
    big_num::BigInteger c = a >> 100;
    ASSERT_EQ(c.ToString(), "1");
}

TEST(Functions, Abs){
    big_num::BigInteger a = -1267650600228229401496703205376_bi;
    big_num::BigInteger c = a.Abs();
    ASSERT_EQ(c.ToString(), "1267650600228229401496703205376");
}

TEST(Functions, AbsWithPositive){
    big_num::BigInteger a = 1267650600228229401496703205376_bi;
    big_num::BigInteger c = a.Abs();
    ASSERT_EQ(c.ToString(), "1267650600228229401496703205376");
}

TEST(Functions, AbsWithZero){
    big_num::BigInteger a = 0_bi;
    big_num::BigInteger c = a.Abs();
    ASSERT_EQ(c.ToString(), "0");
}

TEST(Functions, AbsWithZeroNegative){
    big_num::BigInteger a = -0_bi;
    big_num::BigInteger c = a.Abs();
    ASSERT_EQ(c.ToString(), "0");
}

TEST(Functions, ToStringIntegral){
    big_num::BigFloat a = 1267650600228229401496703205376.12312345_bf;
    ASSERT_EQ(a.ToStringIntegral(), "1267650600228229401496703205376");
}

