#include <gtest/gtest.h>
#include "BigInteger.h"

TEST(Creation, EmptyConstructor) {
    big_num::BigInteger a;
    ASSERT_EQ(a.IsPositive(), true);
    ASSERT_EQ(a.GetIntegralSize(), 0);
    ASSERT_EQ(a.GetFractionSize(), 0);
}

TEST(Creation, StringConstructor) {
    str::string str_num = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    big_num::BigInteger a{str_num};
    ASSERT_EQ(a.IsPositive(), true);
    ASSERT_EQ(str_num, a.ToString());
}