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