//
// Created by Егор Кулин on 15.02.2024.
//
#include <gtest/gtest.h>
#include "BigInteger.h"
TEST(Fractional, CreateFractional){
    big_num::BigInteger a = 0.00052355_bi;
    std::cout << a.ToString() << std::endl;
    ASSERT_EQ(a.ToString(), "0.00052355");
}