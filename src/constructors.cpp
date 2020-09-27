#include "lab3.h"

//namespace lab3 {
//
//    BigInt::BigInt(BigInt &bigInt) {
//        value = bigInt.value;
//        sign = bigInt.sign;
//    }
//
//    BigInt::BigInt() {
//        value = '0';
//        sign = '+';
//    }
//
//    BigInt::BigInt(const std::string &num) {
//        if (num[0] == '+' or num[0] == '-') { // check sign
//            std::string magnitude = num.substr(1);
//            if (isValidNum(magnitude)) { // check validity of magnitude
//                value = magnitude;
//                sign = num[0];
//            } else {
//                throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
//            }
//        } else { // if there is no sign specified
//            if (isValidNum(num)) {
//                value = num;
//                sign = '+'; // + by default
//            } else {
//                throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
//            }
//        }
//        delLeadingZeroes(value);
//    }
//
//    BigInt::BigInt(const long &num) {
//        value = std::to_string(std::abs(num));
//        if (num < 0)
//            sign = '-';
//        else
//            sign = '+';
//
//    }
//
//    BigInt::BigInt(const BigInt &bigInt) {
//        value = bigInt.value;
//        sign = bigInt.sign;
//    }
//}