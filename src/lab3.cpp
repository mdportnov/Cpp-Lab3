#include "lab3.h"
#include <bits/stdc++.h>
#include "vector"

namespace lab3 {
    bool isValidNum(const std::string &num) {
        if (std::all_of(num.begin(), num.end(), [](char digit) {
            return (digit >= '0' and digit <= '9');
        }))
            return true;
        return false;
    }

    void delLeadingZeroes(std::string &num) {
        size_t i;
        for (i = 0; i < num.size(); i++)
            if (num[i] != '0')
                break;
        if (i == num.size())
            num = "0";
        else
            num = num.substr(i);
    }

    void addLeadingZeroes(std::string &num, size_t numOfZeroes) {
        num = std::string(numOfZeroes, '0') + num;
    }

    void addEndingZeroes(std::string &num, size_t num_zeroes) {
        num += std::string(num_zeroes, '0');
    }

    void
    getLargerAndSmaller(std::string &larger, std::string &smaller, const std::string &num1, const std::string &num2) {
        if (num1.size() > num2.size() or (num1.size() == num2.size() and num1 > num2)) {
            larger = num1;
            smaller = num2;
        } else {
            larger = num2;
            smaller = num1;
        }

        // add zeroes to the smaller number
        addLeadingZeroes(smaller, larger.size() - smaller.size());
    }

    BigInt::BigInt(BigInt &bigInt) {
        value = bigInt.value;
        sign = bigInt.sign;
    }

    BigInt::BigInt() {
        value = '0';
        sign = '+';
    }

    BigInt::BigInt(const std::string &num) {
        if (num[0] == '+' or num[0] == '-') { // check sign
            std::string magnitude = num.substr(1);
            if (isValidNum(magnitude)) { // check validity of magnitude
                value = magnitude;
                sign = num[0];
            } else {
                throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
            }
        } else { // if there is no sign specified
            if (isValidNum(num)) {
                value = num;
                sign = '+'; // + by default
            } else {
                throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
            }
        }
        delLeadingZeroes(value);
    }

    BigInt::BigInt(const long &num) {
        value = std::to_string(std::abs(num));
        if (num < 0)
            sign = '-';
        else
            sign = '+';

    }

    BigInt::BigInt(const BigInt &bigInt) {
        value = bigInt.value;
        sign = bigInt.sign;
    }

    void BigInt::swap(BigInt &b) {
        std::swap(value, b.value);
        std::swap(sign, b.sign);
    }

    std::ostream &operator<<(std::ostream &out, const BigInt &n) {
        if (n.sign == '-')
            out << n.sign;
        out << n.value;

        return out;
    }

    std::istream &operator>>(std::istream &in, BigInt &n) {
        std::string input;
        in >> input;
        n = BigInt(input);

        return in;
    }

    BigInt abs(const BigInt &num) {
        return num.sign == '-' ? BigInt(num) : num;
    }

    BigInt &BigInt::operator=(const BigInt &num) = default;

    BigInt &BigInt::operator=(const long &num) {
        BigInt temp(num);
        value = temp.value;
        sign = temp.sign;

        return *this;
    }

    BigInt BigInt::operator~() const {
        if (value.empty()) {
            BigInt bigInt("1");
            return bigInt;
        }

        if (sign == '+') {
            BigInt bigInt(value);
            bigInt.sign = sign;
            return bigInt;
        }

        std::stringstream ss;
        std::string res;

        for (char i : value) {
            char s = '9' - (i - '0');
            ss << s;
        }

        ss >> res;
        BigInt out(res), add("1");
//        out = out + "";
        out.sign = '+';

        return out;
    }

    BigInt BigInt::operator-(const BigInt &num) const {
        // if the operands are of opposite signs, perform addition
        if (this->sign == '+' and num.sign == '-') {
            BigInt rhs = num;
            rhs.sign = '+';
            return *this + rhs;
        } else if (this->sign == '-' and num.sign == '+') {
            BigInt lhs = *this;
            lhs.sign = '+';
            return -(lhs + num);
        }

        BigInt result;      // the resultant difference
        // identify the numbers as `larger` and `smaller`
        std::string larger, smaller;
        if (abs(*this) > abs(num)) {
            larger = this->value;
            smaller = num.value;

            if (this->sign == '-')      // -larger - -smaller = -result
                result.sign = '-';
        } else {
            larger = num.value;
            smaller = this->value;

            if (num.sign == '+')        // smaller - larger = -result
                result.sign = '-';
        }
        // pad the smaller number with zeroes
        addLeadingZeroes(smaller, larger.size() - smaller.size());

        result.value = "";  // the value is cleared as the digits will be appended
        short difference;
        long i, j;
        // subtract the two values
        for (i = larger.size() - 1; i >= 0; i--) {
            difference = larger[i] - smaller[i];
            if (difference < 0) {
                for (j = i - 1; j >= 0; j--) {
                    if (larger[j] != '0') {
                        larger[j]--;    // borrow from the j-th digit
                        break;
                    }
                }
                j++;
                while (j != i) {
                    larger[j] = '9';    // add the borrow and take away 1
                    j++;
                }
                difference += 10;   // add the borrow
            }
            result.value = std::to_string(difference) + result.value;
        }
        delLeadingZeroes(result.value);

        // if the result is 0, set its sign as +
        if (result.value == "0")
            result.sign = '+';

        return result;
    }

    BigInt BigInt::operator+(const BigInt &num) const {
        // if the operands are of opposite signs, perform subtraction
        if (this->sign == '+' and num.sign == '-') {
            BigInt rhs = num;
            rhs.sign = '+';
            return *this - rhs;
        } else if (this->sign == '-' and num.sign == '+') {
            BigInt lhs(value);
            lhs.sign = sign;

            lhs.sign = '+';
            return -(lhs - num);
        }

        // identify the numbers as `larger` and `smaller`
        std::string larger, smaller;
        getLargerAndSmaller(larger, smaller, this->value, num.value);

        BigInt result;      // the resultant sum
        result.value = "";  // the value is cleared as the digits will be appended
        short carry = 0, sum;
        // add the two values
        for (long i = larger.size() - 1; i >= 0; i--) {
            sum = larger[i] - '0' + smaller[i] - '0' + carry;
            result.value = std::to_string(sum % 10) + result.value;
            carry = sum / (short) 10;
        }
        if (carry)
            result.value = std::to_string(carry) + result.value;

        // if the operands are negative, the result is negative
        if (this->sign == '-' and result.value != "0")
            result.sign = '-';

        return result;
    }

    BigInt BigInt::operator+() {
        return *this;
    }

    BigInt BigInt::operator-() const {
        BigInt temp;

        temp.value = value;
        if (value != "0") {
            if (sign == '+')
                temp.sign = '-';
            else
                temp.sign = '+';
        }

        return temp;
    }

    bool BigInt::operator>(const BigInt &num) const {
        return !((*this < num) or (*this == num));
    }

    bool BigInt::operator<(const BigInt &num) const {
        if (sign == num.sign) {
            if (sign == '+') {
                if (value.length() == num.value.length())
                    return value < num.value;
                else
                    return value.length() < num.value.length();
            } else
                return -(*this) > -num;
        } else
            return sign == '-';
    }

    bool BigInt::operator==(const BigInt &num) const {
        return (sign == num.sign) and (value == num.value);
    }


    const char *msgs2[] = {" 0. Exit",
                           " 1. +"
                           " 2. -"
    };

    int addition(BigInt &a, BigInt &b) {
        std::cout << "Result of A+B: " << a + b << std::endl;
        return 1;
    }

    int subtraction(BigInt &a, BigInt &b) {
        std::cout << "Result of A-B: " << a - b << std::endl;;
        return 1;
    }

    int getNaturalInt(int *a) {
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0)
                return 0;
            if (n == 0 || *a < 0) {
                printf("%s\n", "Error! Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0 || *a < 0);
        return 1;
    }

    int dialog(const char *msgs[], int N) {
        std::string errmsg;
        int rc, n;
        do {
            std::cout << errmsg;
            errmsg = "You are wrong. Repeat, please\n";
            for (int j = 0; j < N; ++j)
                puts(msgs[j]);
            puts("Make your choice: --> ");

            n = getNaturalInt(&rc);
            if (n == 0)
                rc = 0;
        } while (rc < 0 || rc >= N);
        return rc;
    }

    const int NMsgs2 = sizeof(msgs2) / sizeof(msgs2[0]);

    int (*functions2[])(BigInt &, BigInt &){nullptr, addition, subtraction};

    int dialog_input() {
        BigInt a;
        BigInt b;
        std::cout << "Input A: ";
        std::cin >> a;
        std::cout << "Input B: ";
        std::cin >> b;

        int rc;
        while ((rc = dialog(msgs2, NMsgs2))) {
            if (!functions2[rc](a, b))
                break;
        }

        return 1;
    }

}