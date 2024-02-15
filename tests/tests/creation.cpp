#include <gtest/gtest.h>
#include "BigInteger.h"

TEST(Creation, EmptyConstructor) {
    big_num::BigInteger a;
    ASSERT_EQ(a.IsPositive(), true);
}

TEST(Creation, StringConstructor) {
    std::string str_num = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    big_num::BigInteger a{str_num};
    ASSERT_EQ(a.IsPositive(), true);
    ASSERT_EQ(str_num, a.ToString());
}

TEST(Creation, CopyConstructor) {
    std::string str_num = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    big_num::BigInteger a{str_num};
    big_num::BigInteger b{a};
    ASSERT_EQ(a.IsPositive(), b.IsPositive());
    ASSERT_EQ(a.ToString(), b.ToString());
}

TEST(Creation, AssignmentOperator) {
    std::string str_num = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    big_num::BigInteger a{str_num};
    big_num::BigInteger b;
    b = a;
    ASSERT_EQ(a.IsPositive(), b.IsPositive());
    ASSERT_EQ(a.ToString(), b.ToString());
}

TEST(Creation, CreateFromLiteral) {
    big_num::BigInteger a = 1234567890_bi;
    ASSERT_EQ(a.IsPositive(), true);
    ASSERT_EQ(a.ToString(), "1234567890");
}

TEST(Creation, CreateFromNegativeLiteral) {
    big_num::BigInteger a = -1234567890_bi;
    ASSERT_EQ(a.IsPositive(), false);
    ASSERT_EQ(a.ToString(), "-1234567890");
}

TEST(Creation, CreateFromBinary) {
    big_num::BigInteger a = big_num::BigInteger::CreateFromBinary("1100100");
    ASSERT_EQ(a.IsPositive(), true);
    ASSERT_EQ(a.ToString(), "100");
}
