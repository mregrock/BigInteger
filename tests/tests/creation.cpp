#include <gtest/gtest.h>
#include "BigInteger.h"
#include "BigFloat.h"

TEST(Creation, EmptyConstructor) {
    big_num::BigInteger a;
    ASSERT_EQ(a.IsPositive(), true);
}

TEST(Creation, FractionalEmptyConstructor) {
    big_num::BigFloat a;
    ASSERT_EQ(a.IsPositive(), true);
}

TEST(Creation, StringConstructor) {
    std::string str_num = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    big_num::BigInteger a{str_num};
    ASSERT_EQ(a.IsPositive(), true);
    ASSERT_EQ(str_num, a.ToString());
}

TEST(Creation, NegativeStringConstructor) {
    std::string str_num = "-123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    big_num::BigInteger a{str_num};
    ASSERT_EQ(a.IsPositive(), false);
    ASSERT_EQ(str_num, a.ToString());
}

TEST(Creation, FractionalStringConstructor){
    std::string str_num = "1234567890.1234567890";
    big_num::BigFloat a{str_num};
    ASSERT_EQ(a.IsPositive(), true);
    //no sense to check the string representation of the number because of the floating point precision
}


TEST(Creation, NegativeFractionalStringConstructor){
    std::string str_num = "-1234567890.1234567890";
    big_num::BigFloat a{str_num};
    ASSERT_EQ(a.IsPositive(), false);
    //no sense to check the string representation of the number because of the floating point precision
}

TEST(Creation, CopyConstructor) {
    std::string str_num = "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
    big_num::BigInteger a{str_num};
    big_num::BigInteger b{a};
    ASSERT_EQ(a.IsPositive(), b.IsPositive());
    ASSERT_EQ(a.ToString(), b.ToString());
}

TEST(Creation, FractionalCopyConstructor) {
    std::string str_num = "1234567890.1234567890";
    big_num::BigFloat a{str_num};
    big_num::BigFloat b{a};
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

TEST(Creation, FractionalAssignmentOperator) {
    std::string str_num = "1234567890.1234567890";
    big_num::BigFloat a{str_num};
    big_num::BigFloat b;
    b = a;
    ASSERT_EQ(a.IsPositive(), b.IsPositive());
    //no sense to check the string representation of the number because of the floating point precision
}
TEST(Creation, CreateFromLiteral) {
    big_num::BigInteger a = 1234567890_bi;
    ASSERT_EQ(a.IsPositive(), true);
    ASSERT_EQ(a.ToString(), "1234567890");
}

TEST(Creation, CreateFromZeroLiteral) {
    big_num::BigInteger a = 0_bi;
    ASSERT_EQ(a.ToString(), "0");
}

TEST(Creation, CreateFromNegativeZeroLiteral) {
    big_num::BigInteger a = -0_bi;
    ASSERT_EQ(a.ToString(), "0");
    ASSERT_EQ(a, 0_bi);
}

TEST(Creation, FractionalCreateFromLiteral) {
    big_num::BigFloat a = 1234567890.1234567890_bf;
    ASSERT_EQ(a.IsPositive(), true);
    //no sense to check the string representation of the number because of the floating point precision
}

TEST(Creation, CreateFromNegativeLiteral) {
    big_num::BigInteger a = -1234567890_bi;
    ASSERT_EQ(a.IsPositive(), false);
    ASSERT_EQ(a.ToString(), "-1234567890");
}

TEST(Creation, FractionalCreateFromNegativeLiteral) {
    big_num::BigFloat a = -1234567890.1234567890_bf;
    ASSERT_EQ(a.IsPositive(), false);
    //no sense to check the string representation of the number because of the floating point precision
}

TEST(Creation, FractionalCreateFromNegativeZeroLiteral) {
    big_num::BigFloat a = -0_bf;
    ASSERT_TRUE(a == 0_bf);
}
TEST(Creation, CreateFromBinary) {
    big_num::BigInteger a = big_num::BigInteger::CreateFromBinary("1100100");
    ASSERT_EQ(a.IsPositive(), true);
    ASSERT_EQ(a.ToString(), "100");
}

TEST(Creation, CreateFromNegativeBinary) {
    big_num::BigInteger a = big_num::BigInteger::CreateFromBinary("-1100100");
    ASSERT_EQ(a.IsPositive(), false);
    ASSERT_EQ(a.ToString(), "-100");
}

TEST(Creation, CreateFromBinaryWithLeadingZeroes) {
    big_num::BigInteger a = big_num::BigInteger::CreateFromBinary("-00001100100");
    ASSERT_EQ(a.IsPositive(), false);
    ASSERT_EQ(a.ToString(), "-100");
}

TEST(Creation, CreateFromBinaryWithLeadingZeroes2) {
    big_num::BigInteger a = big_num::BigInteger::CreateFromBinary("00001100100");
    ASSERT_EQ(a.IsPositive(), true);
    ASSERT_EQ(a.ToString(), "100");
}