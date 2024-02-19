//
// Created by Егор Кулин on 15.02.2024.
//
#include <gtest/gtest.h>
#include "BigInteger.h"
#include "BigFloat.h"

TEST(Subtraction, SimpleSubtraction){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = 9876543210_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "-8641975320");
}

TEST(Subtraction, SubtractionWithCarry){
    big_num::BigInteger a = 10000000000_bi;
    big_num::BigInteger b = 1_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "9999999999");
}

TEST(Subtraction, SubtractionWithNegative){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = -1234567890_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "2469135780");
}

TEST(Subtraction, SubtractionWithNegativeAndCarry){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = -1234567891_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "2469135781");
}

TEST(Subtraction, SubtractionWithDifferentSize){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = 12345678901234567890_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "-12345678900000000000");
}

TEST(Subtraction, SubtractionWithDifferentSizeAndCarry){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = 12345678901234567890_bi;
    big_num::BigInteger c = b - a;
    ASSERT_EQ(c.ToString(), "12345678900000000000");
}

TEST(Subtraction, SubtractionWithDifferentSizeAndNegative){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = -12345678901234567890_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "12345678902469135780");
}

TEST(Subtraction, SubtractionWithDifferentSizeAndNegativeAndCarry){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = -12345678901234567891_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "12345678902469135781");
}

TEST(Subtraction, SubtractionWithDifferentSizeAndNegativeAndCarry2){
    big_num::BigInteger a = 1234567890_bi;
    big_num::BigInteger b = -12345678901234567890_bi;
    big_num::BigInteger c = b - a;
    ASSERT_EQ(c.ToString(), "-12345678902469135780");
}

TEST(Subtraction, NegativeSubtraction){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = -9876543210_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "8641975320");
}

TEST(Subtraction, NegativeSubtractionWithCarry){
    big_num::BigInteger a = -10000000000_bi;
    big_num::BigInteger b = -1_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "-9999999999");
}

TEST(Subtraction, NegativeSubtractionWithNegative){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = 1234567890_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "-2469135780");
}

TEST(Subtraction, NegativeSubtractionWithNegativeAndCarry){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = 1234567891_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "-2469135781");
}

TEST(Subtraction, NegativeSubtractionWithDifferentSize){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = 12345678901234567890_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "-12345678902469135780");
}

TEST(Subtraction, NegativeSubtractionWithDifferentSizeAndCarry){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = 12345678901234567890_bi;
    big_num::BigInteger c = b - a;
    ASSERT_EQ(c.ToString(), "12345678902469135780");
}

TEST(Subtraction, NegativeSubtractionWithDifferentSizeAndNegative){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = -12345678901234567890_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "12345678900000000000");
}

TEST(Subtraction, NegativeSubtractionWithDifferentSizeAndNegativeAndCarry){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = -12345678901234567891_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "12345678900000000001");
}

TEST(Subtraction, NegativeSubtractionWithDifferentSizeAndNegativeAndCarry2){
    big_num::BigInteger a = -1234567890_bi;
    big_num::BigInteger b = -12345678901234567890_bi;
    big_num::BigInteger c = b - a;
    ASSERT_EQ(c.ToString(), "-12345678900000000000");
}

TEST(Subtraction, SubtractionWithZero){
    big_num::BigInteger a = 0_bi;
    big_num::BigInteger b = 0_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "0");
}

TEST(Subtraction, SubtractionWithZeroAndNegative){
    big_num::BigInteger a = 0_bi;
    big_num::BigInteger b = -0_bi;
    big_num::BigInteger c = a - b;
    ASSERT_EQ(c.ToString(), "0");
}

TEST(Subtraction, FractionalSubtraction){
    big_num::BigFloat a = 123312312345673213.129978933_bf;
    big_num::BigFloat b = 9873456789570.45497897896_bf;
    big_num::BigFloat c = a - b;
    std::string res = "123302438888883642.67499995404";
    ASSERT_TRUE((c - big_num::BigFloat(res)).Abs() < 1_bf / 100);
}

TEST(Subtraction, FractionalSubtractionWithNegative){
    big_num::BigFloat a = 123312312345673213.129978933_bf;
    big_num::BigFloat b = -9873456789570.45497897896_bf;
    big_num::BigFloat c = a - b;
    std::string res = "123322185802462783.58495791196";
    ASSERT_TRUE((c - big_num::BigFloat(res)).Abs() < 1_bf / 100);
}

TEST(Subtraction, NegativeFractionalSubtraction){
    big_num::BigFloat a = -123312312345673213.129978933_bf;
    big_num::BigFloat b = 9873456789570.45497897896_bf;
    big_num::BigFloat c = a - b;
    std::string res = "-123322185802462783.58495791196";
    ASSERT_TRUE((c - big_num::BigFloat(res)).Abs() < 1_bf / 100);
}

TEST(Subtraction, NegativeFractionalSubtractionWithNegative){
    big_num::BigFloat a = -123312312345673213.129978933_bf;
    big_num::BigFloat b = -9873456789570.45497897896_bf;
    big_num::BigFloat c = a - b;
    std::string res = "-123302438888883642.67499995404";
    ASSERT_TRUE((c - big_num::BigFloat(res)).Abs() < 1_bf / 100);
}

TEST(Subtraction, SubtractionWithZeroFractional){
    big_num::BigFloat a = 123312312345673213.129978933_bf;
    big_num::BigFloat b = 123312312345673213.129978933_bf;
    big_num::BigFloat c = a - b;
    ASSERT_EQ(c.ToString(), "0");
}

