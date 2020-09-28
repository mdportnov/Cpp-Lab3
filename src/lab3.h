#include <limits>
#include "string"
#include "iostream"

namespace lab3 {

    int dialog_input();

    class BigInt;

    bool isValidNum(const std::string &);

    void delLeadingZeroes(std::string &);

    void addLeadingZeroes(std::string &, size_t);

    void addEndingZeroes(std::string &, size_t);

    void
    getLargerAndSmaller(std::string &larger, std::string &smaller, const std::string &num1, const std::string &num2);

    int dialog(const char *[], int);

    BigInt abs(const BigInt &num);

    class BigInt {
        bool sign;
        uint8_t* value;

    public:
        friend BigInt abs(const BigInt &num);

        // Constructors
        BigInt(); // default
        explicit BigInt(const long &); // long
        explicit BigInt(const std::string &); // string
        BigInt(const BigInt &); // copy constructor
        BigInt(BigInt &); // copy constructor

        std::string getString();

        // io stream operators
        friend std::istream &operator>>(std::istream &in, BigInt &n);

        friend std::ostream &operator<<(std::ostream &out, BigInt const &n);

        // assignment operator
        BigInt &operator=(const BigInt &num);

        BigInt &operator=(const long &num);

        // unary arithmetic operations
        BigInt operator+();

        BigInt operator-() const;

        // binary arithmetic operations
        BigInt operator+(const BigInt &num) const;

        BigInt operator-(const BigInt &num) const;

        BigInt operator~() const;

        // Деструкторы
        // Копирующий и перемещающий конструкторы
        // value на массив u_int_8t
        // перемещающий конструктор a+b=c / вместо двух раз вызовется вызов памяти один раз

        bool operator==(const BigInt &num) const;

        bool operator>(const BigInt &num) const;

        bool operator<(const BigInt &num) const;

        void swap(BigInt &);
    };
}
