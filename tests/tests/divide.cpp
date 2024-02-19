//
// Created by Егор Кулин on 17.02.2024.
//
#include <gtest/gtest.h>
#include "BigInteger.h"
#include "BigFloat.h"
TEST(Divide, SimplestDivide){
    big_num::BigFloat a = 5_bf;
    big_num::BigFloat b = 4_bf;
    big_num::BigFloat c = a / b;
    ASSERT_EQ(c.ToString(), "1.25");
}
TEST(Divide, SimpleDivide){
    big_num::BigFloat a = 568_bf;
    big_num::BigFloat b = 541_bf;
    big_num::BigFloat c = a / b;
    ASSERT_EQ(c.ToString(100), "1.0499075785582255083179297597042513863216266173752310536044362292051756007393715341959334565619223659");
}

TEST(Divide, DivideWithNegative){
    big_num::BigFloat a = 568_bf;
    big_num::BigFloat b = -541_bf;
    big_num::BigFloat c = a / b;
    ASSERT_EQ(c.ToString(100), "-1.0499075785582255083179297597042513863216266173752310536044362292051756007393715341959334565619223659");
}

TEST(Divide, NegativeDivide){
    big_num::BigFloat a = -568_bf;
    big_num::BigFloat b = 541_bf;
    big_num::BigFloat c = a / b;
    ASSERT_EQ(c.ToString(100), "-1.0499075785582255083179297597042513863216266173752310536044362292051756007393715341959334565619223659");
}

TEST(Divide, NegativeDivideWithNegative){
    big_num::BigFloat a = -568_bf;
    big_num::BigFloat b = -541_bf;
    big_num::BigFloat c = a / b;
    ASSERT_EQ(c.ToString(100), "1.0499075785582255083179297597042513863216266173752310536044362292051756007393715341959334565619223659");
}

TEST(Divide, DivideByZero){
    big_num::BigFloat a = 568_bf;
    big_num::BigFloat b = 0_bf;
    ASSERT_THROW(a / b, std::overflow_error);
}

TEST(Divide, DivideZeroByZero){
    big_num::BigFloat a = 0_bf;
    big_num::BigFloat b = 0_bf;
    ASSERT_THROW(a / b, std::overflow_error);
}

TEST(Divide, DivideZeroByInteger){
    big_num::BigInteger a = 0_bi;
    big_num::BigInteger b = 568_bi;
    big_num::BigInteger c = a / b;
    ASSERT_EQ(c.ToString(), "0");
}
TEST(Divide, DivideZeroByNumber){
    big_num::BigFloat a = 0_bf;
    big_num::BigFloat b = 568_bf;
    big_num::BigFloat c = a / b;
    ASSERT_TRUE((c - 0_bf).Abs() < 1_bf / 100);
}

