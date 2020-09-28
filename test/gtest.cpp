#include "gtest/gtest.h"
#include "../src/lab3.cpp"

TEST(BigIntConstructor, DefaultConstructor) {
    lab3::BigInt bigInt("");
    ASSERT_EQ("0", bigInt.getString());
}

TEST(BigIntConstructor, StringConstructor) {
    lab3::BigInt bigInt("4321");
    ASSERT_EQ("4321", bigInt.getString());
}

TEST(BigIntConstructor, TestException) {
    ASSERT_ANY_THROW(lab3::BigInt("432asd").getString());
}

TEST(BigIntOperator, OperatorAdd) {
    lab3::BigInt bigInt1("4321");
    lab3::BigInt bigInt2("4321");
    lab3::BigInt bigInt3 = bigInt1 + bigInt2;
    ASSERT_EQ("8642", bigInt3.getString());
}

TEST(BigIntOperator, OperatorSub) {
    lab3::BigInt bigInt1("4321");
    lab3::BigInt bigInt2("4321");
    lab3::BigInt bigInt3 = bigInt1 - bigInt2;
    ASSERT_EQ("0", bigInt3.getString());
}

TEST(BigIntOperator, OperatorEqual) {
    lab3::BigInt bigInt1("4321");
    lab3::BigInt bigInt2("4321");
    bool isTrue = bigInt2 == bigInt1;
    ASSERT_EQ(true, isTrue);
}
// сложение вычитание разных разрядов

// сколько кода покрыто тестами

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}