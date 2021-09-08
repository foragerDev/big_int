
#ifndef BIG_INT
#define BIG_INT

#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

class BigInt
{
private:
    std::string m_value;
    bool m_is_negative;

    // Helper Methods
    void remove_lead_zeros(const std::string &value);
    bool is_number(const std::string &str_value) const;
    BigInt handle_add(BigInt &first_op, BigInt &second_op);
    BigInt handle_subtract(BigInt &first_op, BigInt &second_op);

    std::string slow_multiply(const std::string &first_op, const std::string &second_op) const;
    std::string karatsuba_multiply(const std::string &first_op, const std::string &second_op) const;
    std::string helper_adder(const std::string &first_op, const std::string &second_op) const;
    std::string helper_subtractor(const std::string &first_op, const std::string &second_op) const;

    std::pair<BigInt, BigInt> div_mod(BigInt &divider);

    void read();
    void print();

public:
    explicit BigInt();
    explicit BigInt(const long long num);
    BigInt(const std::string &str_value);

    // Getter and Setters

    template <typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
    void set_value(T num)
    {
        if (num < 0)
        {
            m_is_negative = true;
            num = std::abs(num);
        }
        m_is_negative = false;
        m_value = std::to_string(num);
    }
    void set_value(const std::string &str_value);
    std::string &get_value();

    bool is_greater(const BigInt &other) const;
    bool is_smaller(const BigInt &other) const;
    bool is_equal(const BigInt &other) const;

    bool is_zero() const;
    bool fits_in_ll() const;
    int digit_count() const;

    void absolute();
    BigInt &multiply_10(int count = 1);
    BigInt &divide_10(int count = 1);

    BigInt &add(const BigInt &num);
    BigInt &subtract(const BigInt &num);
    BigInt &multiply(const BigInt &muliplier);
    BigInt &divide(const BigInt &divider);
    BigInt &modulo(const BigInt &num);

    BigInt &operator+(const BigInt &second_op);
    BigInt &operator-(const BigInt &second_op);
    BigInt &operator*(const BigInt &second_op);
    BigInt &operator/(const BigInt &second_op);
    BigInt &operator%(const BigInt &second_op);
    BigInt &operator+=(const BigInt &second_op);
    BigInt &operator-=(const BigInt &second_op);
    BigInt &operator*=(const BigInt &second_op);
    BigInt &operator/=(const BigInt &second_op);
    BigInt &operator%=(const BigInt &second_op);

    template <typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
    BigInt &operator+(const T &second_op)
    {
    }
    template <typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
    BigInt &operator-(const T &second_op)
    {
    }
    template <typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
    BigInt &operator*(const T &second_op)
    {
    }
    template <typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
    BigInt &operator/(const T &second_op)
    {
    }
    template <typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
    BigInt &operator%(const T &second_op)
    {
    }
    template <typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
    BigInt &operator+=(const T &second_op)
    {
    }
    template <typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
    BigInt &operator-=(const T &second_op)
    {
    }
    template <typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
    BigInt &operator*=(const T &second_op)
    {
    }
    template <typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
    BigInt &operator/=(const T &second_op)
    {
    }
    template <typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
    BigInt &operator%=(const T &second_op)
    {
    }

    BigInt &operator++(int);
    BigInt &operator++();
    BigInt &operator--(int);
    BigInt &operator--();

    friend BigInt abs(BigInt &num);
    friend std::ostream &operator<<(std::ostream &, BigInt &big_int);
    friend std::istream &operator>>(std::istream &, BigInt &big_int);

    friend bool operator<(const BigInt &lhs, const BigInt &rhs);
    friend bool operator>(const BigInt &lhs, const BigInt &rhs);
    friend bool operator==(const BigInt &lhs, const BigInt &rhs);
    friend bool operator>=(const BigInt &lhs, const BigInt &rhs);
    friend bool operator<=(const BigInt &lhs, const BigInt &rhs);
    friend bool operator!=(const BigInt &lhs, const BigInt &rh);
};

#endif