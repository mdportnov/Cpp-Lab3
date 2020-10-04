#include <limits>
#include "string"
#include "iostream"

namespace lab3 {

    int dialog_input();

    class BigInt;

    int dialog(const char *[], int);

    class BigInt {
    private:
        int length;
        char *value;

        BigInt(const BigInt &, int);

        BigInt(int, int);

        void correction();

    public:
        BigInt();

        explicit BigInt(std::istream &in) : BigInt() { in >> *this; };

        explicit BigInt(long int num);

        explicit BigInt(int num);

        explicit BigInt(const char *);

        // конструктор перемещения
        BigInt(BigInt &&num) noexcept: length(num.length), value(num.value) { num.value = nullptr; }

        BigInt(const BigInt &);

        BigInt operator~() const;

        friend std::istream &operator>>(std::istream &, BigInt &);

        friend std::ostream &operator<<(std::ostream &, const BigInt &);

        friend BigInt operator+(const BigInt &, const BigInt &);

        BigInt operator-() const;

        friend BigInt operator-(const BigInt &a, const BigInt &b) {
            return a + (-b);
        };

        friend BigInt &operator+=(BigInt &left, const BigInt &right) {
            left = left + right;
            return left;
        };

        friend BigInt &operator-=(BigInt &left, const BigInt &right) {
            left = left + (-right);
            return left;
        };

        BigInt operator*(const int &);

        BigInt operator/(const int &);

        friend BigInt &operator*=(BigInt &left, const int &right) {
            left = left * right;
            return left;
        };

        friend BigInt &operator/=(BigInt &left, const int &right) {
            left = left / right;
            return left;
        };

        BigInt &operator=(const BigInt &);

        BigInt &operator=(BigInt &&); // оператор перемещения

        explicit operator int() const;

        ~BigInt() { delete[]value; }
    };
}
