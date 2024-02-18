//
// Created by Егор Кулин on 15.02.2024.
//
#include <gtest/gtest.h>
#include "BigInteger.h"
#include "BigFloat.h"

TEST(Fractional, DivideFractional){
    big_num::BigFloat a = 2.25_bf;
    big_num::BigFloat b = 1.5_bf;
    big_num::BigFloat c = a / b;
    ASSERT_EQ(c.ToString(), "1.5");
}
TEST(Fractional, CreateFractional){
    big_num::BigFloat a = 568_bf;
    big_num::BigFloat b = 541_bf;
    big_num::BigFloat c = a / b;
    ASSERT_EQ(c.ToString(), "1.25");
}