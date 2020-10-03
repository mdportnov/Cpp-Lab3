#include "gtest/gtest.h"
#include "../src/lab3.cpp"

using namespace lab3;

TEST(BigIntConstructor, DefaultConstructor) {
    ASSERT_EQ(0, (int) BigInt());
}

TEST(BigIntConstructor, StringConstructor) {
    ASSERT_EQ(0, (int) BigInt("0"));
    ASSERT_EQ(-1, (int) BigInt("-1"));
    ASSERT_EQ(1, (int) BigInt("1"));
    ASSERT_EQ(0, (int) BigInt(nullptr));
    ASSERT_EQ(0, (int) BigInt("1x"));
}

TEST(BigIntConstructor, IntConstructor) {
    ASSERT_EQ(0, (int) BigInt(0));
    ASSERT_EQ(-1, (int) BigInt(-1));
    ASSERT_EQ(1, (int) BigInt(1));
    ASSERT_EQ(100, (int) BigInt(100));
    ASSERT_EQ(-100, (int) BigInt(-100));
}

TEST(Operator, tildaOperator) {
    ASSERT_EQ(0, (int) ~BigInt(0));
    ASSERT_EQ(-9, (int) ~BigInt(-1));
}

TEST(Operator, unMinusOperator) {
    ASSERT_EQ(0, (int) -BigInt(0));
    ASSERT_EQ(-11, (int) -BigInt(11));
    ASSERT_EQ(11, (int) -BigInt(-11));
}

TEST(Operator, sumOperator) {
    ASSERT_EQ(1, (int) BigInt(-1) + 2);
    ASSERT_EQ(-1, (int) BigInt(-1) + 0);
    ASSERT_EQ(10000, (int) BigInt(-1) + 10001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}