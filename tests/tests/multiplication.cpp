//
// Created by Егор Кулин on 15.02.2024.
//
#include <gtest/gtest.h>
#include "BigInteger.h"
#include "BigFloat.h"

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

TEST(Multiplication, BigMultiplication){
    big_num::BigInteger a = 97804128401274950875667849124005901093812739000_bi;
    big_num::BigInteger b = 899400498400498127480040128476789008_bi;
    big_num::BigInteger c = a * b;
    ASSERT_EQ(c.ToString(), "87965081829733004937029228185750150787294692442594161013397502806255682765572912000");
}

TEST(Multiplication, FractionalMultiplication){
    big_num::BigFloat a = 12345673213.1233_bf;
    big_num::BigFloat b = 9873456789570.4546_bf;
    big_num::BigFloat c = a * b;
    std::string res = "121894471007930336353606.66685218";
    ASSERT_TRUE((c - big_num::BigFloat(res)).Abs() < 1_bf / 100);
}

TEST(Multiplication, BigDivide){
    big_num::BigInteger a = 5_bi;
    big_num::BigInteger b = 4_bi;
    a = a * big_num::BigInteger::Pow(2_bi, 1024);
    b = b * big_num::BigInteger::Pow(2_bi, 512);
    std::cout << a / b << std::endl;
}