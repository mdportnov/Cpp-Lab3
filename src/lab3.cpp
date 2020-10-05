#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#include "lab3.h"
#include <bits/stdc++.h>

namespace lab3 {
    BigInt::BigInt() {
        value = new char[2];
        length = 1;
        value[0] = '0'; // знак
        value[1] = '0';
    }

    BigInt::BigInt(int num) : BigInt() {
        char sgn = num < 0 ? '9' : '0';
        num = num < 0 ? -num : num;
        int i = 10, k = 1;
        while (num / i > 0) {
            i *= 10;
            k++;
        }
        delete[]value;
        value = new char[k + 1];
        length = k;
        value[0] = sgn;
        for (int l = k; l >= 1; l--) {
            value[l] = (char) (((int) '0') + num % 10);
            num /= 10;
        }
    }

    BigInt::BigInt(long int num) : BigInt() {
        value[0] = num < 0 ? '9' : '0';
        num = num < 0 ? -num : num;
        int i = 10, k = 1;
        while (num / i > 0) {
            i *= 10;
            k++;
        }
        delete[]value;
        value = new char[k + 1];

        length = k;
        for (int l = k; l >= 1; l--) {
            value[l] = (char) (((int) '0') + num % 10);
            num /= 10;
        }

    }

    BigInt::BigInt(const char *str) : BigInt() {
//        try {
        if (str == nullptr)
            throw "Nullptr exception";
        bool zero = true;
        char sgn;
        int l = strlen(str), z = 0;
        if (str[0] == '-') {
            sgn = '9';
            z++;
            l--;
        } else sgn = '0';

        if (l != strspn(str + (sgn == '9' ? 1 : 0), "0123456789"))
            throw "Wrong data error!";
        while (zero && l > 0) {
            if (str[z] == '0') {
                z++;
                l--;
            } else zero = false;
        }
        if (!zero) {
            delete[]value;
            value = new char[l + 1];
            length = l;
            value[0] = sgn;
            for (int i = 1; i <= l; i++) {
                value[i] = str[z];
                z++;
            }
        }
    }

    BigInt::BigInt(const BigInt &orig, int m) {
        value = new char[orig.length + m + 1];
        value[0] = orig.value[0];
        int i = 1;
        for (; i <= m; i++)
            value[i] = '0';
        for (; i <= orig.length + m; i++)
            value[i] = orig.value[i - m];
        length = orig.length + m;
    }

    BigInt::BigInt(const BigInt &orig) {
        length = orig.length;
        value = new char[length + 1];
        for (int i = 0; i < length + 1; i++)
            value[i] = orig.value[i];
    }

    BigInt::BigInt(int num, int) {
        length = num;
        if (num == 0)
            length++;
        value = new char[length + 1];
        for (int i = 0; i <= length; i++)
            value[i] = '0';
    }

    BigInt BigInt::operator~() const {
        if (value[0] == '0')
            return *this;
        bool pr = true; // "запас" перенос +1 в след разряд
        BigInt res(length, 1);
        for (int i = length; i > 0; i--) {
            if (pr && value[i] != '0') {
                res.value[i] = (char) 10 - (value[i] - '0') + '0';
                pr = false;
            } else {
                if (!pr)
                    res.value[i] = (char) 9 - (value[i] - '0') + '0';
                else res.value[i] = '0';
            }

        }
        res.value[0] = '9';
        return res;
    }

    std::istream &operator>>(std::istream &in, BigInt &num) {
        try {

            char *n = new char[255];
            in >> n;
            bool zero = true;
            char sgn;
            int l = strlen(n), z = 0;
            if (n[0] == '-') {
                sgn = '9';
                z++;
                l--;
            } else sgn = '0';

            if (l != strspn(n + (sgn == '9' ? 1 : 0), "0123456789"))
                throw "Wrong data error!";
            while (zero && l > 0) {
                if (n[z] == '0') {
                    z++;
                    l--;
                } else zero = false;
            }
            if (zero) {
                delete[]num.value;
                num.length = 1;
                num.value = new char[2];
                num.value[0] = num.value[1] = '0';
            } else {
                delete[]num.value;
                num.value = new char[l + 1];
                num.length = l;
                num.value[0] = sgn;
                for (int i = 1; i <= l && z <= l; i++) {
                    num.value[i] = n[z];
                    z++;
                }
            }
            delete[]n;
        }
        catch (const char *a) {
            if (a == "Wrong data error!") {
                std::cout << "The number should include only '-' at the begin and '0-9' chars." << std::endl;
            }
        }
        catch (...) {
            std::cout << "Nullptr" << std::endl;
        }
    }

    std::ostream &operator<<(std::ostream &out, const BigInt &num) {
        if (num.value[0] == '9')
            out << "-";
        for (int i = 1; i <= num.length; i++)
            out << num.value[i];
        return out;
    }

    BigInt operator+(const BigInt &num, const BigInt &bigInt) {
        BigInt n1(num, num.length > bigInt.length ? 1 : bigInt.length - num.length + 1), n2(~bigInt);
        n1 = ~n1;
        int pr = 0;
        for (int i = n1.length; i > n1.length - n2.length; i--) {
            if (n1.value[i] - '0' + n2.value[i + n2.length - n1.length] - '0' + pr < 10) {
                n1.value[i] = (char) n1.value[i] - '0' + n2.value[i + n2.length - n1.length] - '0' + pr + '0';
                pr = 0;
            } else {
                n1.value[i] =
                        (char) n1.value[i] - '0' + n2.value[i + n2.length - n1.length] - '0' + pr + '0' - 10;
                pr = 1;
            }
        }
        char dop = n2.value[0] == '0' ? '0' : '9';
        for (int i = n1.length - n2.length; i >= 0; i--) {
            if (n1.value[i] - '0' + dop - '0' + pr < 10) {
                n1.value[i] = n1.value[i] + pr + dop - '0';
                pr = 0;
            } else {
                n1.value[i] = n1.value[i] - '0' + dop - '0' + pr + '0' - 10;;
                pr = 1;
            }
        }
        n1 = ~n1;
        n1.correction();
        return n1;
    }

    BigInt BigInt::operator-() const {
        BigInt res = *this;
        for (int i = 0; i <= length; i++) {
            if (value[i] != '0') {
                res.value[0] = value[0] == '0' ? '9' : '0';
                break;
            }
        }
        return res;
    }

    BigInt BigInt::operator*(const int &a) {
        if (length > 1 || value[1] != '0') {
            BigInt res(length + 1, 1);
            for (int i = 0; i <= length; i++)
                res.value[i] = value[i];
            res.value[length + 1] = '0';
            return res;
        } else {
            return *this;
        }
    }

    BigInt BigInt::operator/(const int &i) {
        bool zero = true;
        BigInt res(length - 1, 1);
        for (int j = 0; j < length; j++) {
            res.value[j] = value[j];
            if (zero && j > 0 && value[j] != '0')
                zero = false;
        }
        if (zero) {
            res.value[0] = '0';
            res.length = 1;
            return res;
        }
        return res;
    }

    BigInt &BigInt::operator=(const BigInt &num) {
        if (this->value != num.value) {
            delete[]value;
            if (num.length != 0) {
                length = num.length;
                value = new char[num.length + 1];
                for (int i = 0; i <= length; i++)
                    value[i] = num.value[i];
            }
        }
        return *this;
    }

    BigInt &BigInt::operator=(BigInt &&num) {
        if (value != nullptr) {
            delete[]value;
            value = num.value;
            length = num.length;
            num.value = nullptr;
        }
        return *this;
    }

    BigInt::operator int() const {
        int i = 0;
        int pow = 1;
        if (length > 8)
            throw "Wrong cast";
        for (int k = length; k >= 1; k--) {
            i += (value[k] - '0') * pow;
            pow *= 10;
        }
        i = value[0] == '0' ? i : -i;
        return i;
    }

    void BigInt::correction() {
        if (value[1] == '0') {
            value[0] = (value[0] == '9' ? '-' : '0');
            for (int i = 1; i < length; i++)
                value[i] = value[i + 1];
            value[length] = '\0';
            *this = BigInt(value);
        }
    }

    const char *msgs2[] = {" 0. Exit",
                           " 1. +",
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
        std::cout << "Input A:";
        std::cin >> a;
        std::cout << "Input B:";
        std::cin >> b;

        int rc;
        while ((rc = dialog(msgs2, NMsgs2))) {
            if (!functions2[rc](a, b))
                break;
        }

        return 1;
    }

}
#pragma clang diagnostic pop