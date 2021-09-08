#include <algorithm>
#include <stdexcept>
#include <vector>
#include <limits>
#include "big_int.h"

BigInt::BigInt() : m_value{"0"}, m_is_negative{"false"}
{
    //This is empty.
}

BigInt::BigInt(long long num) : BigInt(std::to_string(num))
{
    //This is empty.
}

BigInt::BigInt(const std::string &str_value) : m_value(str_value)
{
    m_is_negative = m_value[0] == '-' ? true : false;
    if (m_value[0] == '+' || m_value[0] == '-')
        m_value.erase(m_value.begin());
    if (!is_number(m_value))
        throw std::invalid_argument("string is not a valid");
    remove_lead_zeros(m_value);
}

//Helpers
void BigInt::remove_lead_zeros(const std::string &value)
{
    m_value.erase(0, std::min(m_value.find_last_not_of('0'), m_value.size() - 1));
}

bool is_number(const std::string &str_value)
{
    return !str_value.empty() && std::find_if(
                                     str_value.begin(),
                                     str_value.end(),
                                     [](unsigned char c) { return !std::isdigit(c); }) == str_value.end();
}

//Getter and setter
std::string &BigInt::get_value()
{
    if (m_is_negative)
        m_value.insert(m_value.begin(), '-');
    return m_value;
}

void BigInt::set_value(const std::string &str_value)
{
    BigInt temp{str_value};
    *this = temp;
}

//IO operations
void BigInt::read()
{
    std::string value;
    std::cin >> value;
    BigInt temp{value};
    *this = temp;
}

void BigInt::print()
{
    std::cout << get_value();
}

// Comparison methods

bool BigInt::is_greater(const BigInt &other) const
{
    if (!m_is_negative && other.m_is_negative)
        return true;
    if (m_is_negative && !other.m_is_negative)
        return false;
    size_t first_length = m_value.length();
    size_t second_length = other.m_value.length();
    if (first_length != second_length)
    {
        if (m_is_negative && other.m_is_negative)
            return (first_length < second_length);
        return (first_length > second_length);
    }
    for (size_t index = 0; index < first_length; ++index)
    {
        if (m_value[index] == other.m_value[index])
            continue;
        if (m_is_negative && other.m_is_negative)
            return (m_value[index] < other.m_value[index]);
        return (m_value[index] > other.m_value[index]);
    }
    return false;
}

bool BigInt::is_smaller(const BigInt &other) const
{
    if (!m_is_negative && other.m_is_negative)
        return false;
    if (m_is_negative && !other.m_is_negative)
        return true;
    size_t first_length = m_value.length();
    size_t second_length = other.m_value.length();
    if (first_length != second_length)
    {
        if (m_is_negative && other.m_is_negative)
            return (first_length < second_length);
        return (first_length > second_length);
    }
    for (size_t index = 0; index < first_length; ++index)
    {
        if (m_value[index] == other.m_value[index])
            continue;
        if (m_is_negative && other.m_is_negative)
            return (m_value[index] > other.m_value[index]);
        return (m_value[index] < other.m_value[index]);
    }
    return false;
}

bool BigInt::is_equal(const BigInt &other) const
{
    return ((m_value == other.m_value) && (m_is_negative == other.m_is_negative));
}

bool BigInt::is_zero() const
{
    return m_value == "0";
}

bool BigInt::fits_in_ll() const
{
    auto u_max = std::to_string(std::numeric_limits<unsigned long long>::max());
    if (m_is_negative)
    {
        auto min = std::to_string(std::numeric_limits<long long>::min());
        auto max = std::to_string(std::numeric_limits<long long>::max());
        return (m_value <= max && m_value >= min);
    }
    return m_value <= u_max;
}

int BigInt::digit_count() const
{
    return m_value.length();
}

void BigInt::absolute()
{
    m_is_negative = false;
}

BigInt &BigInt::multiply_10(int count)
{
    std::fill_n(std::back_inserter(m_value), count, '0');
    return *this;
}

BigInt &BigInt::divide_10(int count)
{
    if (m_value.length() == 0)
    {
        m_value = "0";
    }
    m_value = m_value.substr(0, m_value.size() - count);
    return *this;
}

std::string BigInt::helper_adder(const std::string &first_op, const std::string &second_op) const
{
    std::string sum;
    int carry = 0;
    int index_a = first_op.length() - 1, index_b = second_op.length() - 1;
    while (index_a >= 0 || index_b >= 0 || carry)
    {
        int current_sum = 0;
        if (index_a >= 0)
            current_sum += (first_op[index_a] - '0'), index_a--;
        if (index_b >= 0)
            current_sum += (second_op[index_b] - '0'), index_b--;
        current_sum += carry;
        sum += ((current_sum % 10) + '0');
        carry = (current_sum / 10);
    }
    std::reverse(sum.begin(), sum.end());
    return sum;
}

std::string BigInt::helper_subtractor(const std::string &first_op, const std::string &second_op) const
{
    std::string result;
    std::string _first_op = first_op;
    std::string _second_op = second_op;
    int index_a = _first_op.length() - 1, index_b = _second_op.length() - 1;
    while (index_a >= 0 && index_b >= 0)
    {
        if (_first_op[index_a] >= _second_op[index_b])
        {
            result += (((_first_op[index_a] - '0') - (_second_op[index_b] - '0') + '0'));
            index_a--, index_b--;
            continue;
        }
        int temp = index_a - 1;
        _first_op[temp] = temp == '0' ? '9' : _second_op[temp]--;
        int y = (_first_op[index_a] - '0') + 10;
        result += ((y - (_second_op[index_b] - '0')) + '0');
    }
    while (index_a >= 0)
        result += m_value[index_a];
    std::reverse(result.begin(), result.end());
    return result;
}

BigInt &BigInt::add(const BigInt &num)
{
    std::string temp;
    if ((m_is_negative && num.m_is_negative) || (!m_is_negative && !num.m_is_negative))
    {
        m_value = helper_adder(m_value, num.m_value);
        return *this;
    }
    return subtract(num);
}

BigInt &BigInt::subtract(const BigInt &num)
{
    if (m_is_negative && num.m_is_negative)
    {
        return this->add(num);
    }
    if (this->is_smaller(num))
    {
        BigInt temp = num;
        *this = temp.subtract(*this);
        return *this;
    }
    m_value = helper_subtractor(m_value, num.m_value);
    remove_lead_zeros(m_value);
    return *this;
}

std::string BigInt::slow_multiply(const std::string &multiple, const std::string &multiplier) const
{
    std::vector<unsigned long long> result{multiple.length() + multiplier.length(), 0};
    for (size_t i = multiple.size(); i >= 0; --i)
    {
        for (size_t j = multiplier.size(); j >= 0; --j)
        {
            result[i + j + 1] = multiple[i] * multiplier[j];
            result[i + j] = result[i + j + 1] / 10;
            result[i + j + 1] %= 10;
        }
    }

    result = {find_if_not(result.begin(), result.end(), [](int a) { return a == 0; }), result.end()};
    return result.empty() ? "0" : std::string(result.begin(), result.end());
}

std::string BigInt::karatsuba_multiply(const std::string &multiple, const std::string &multiplier) const
{
    if (multiple.length() < 10 || multiplier.length() < 10)
    {
        return slow_multiply(multiple, multiplier);
    }
    size_t min_size = std::min(multiple.length(), multiplier.length());
    int mid = min_size / 2;

    std::pair<std::string, std::string> high_low_1 = {
        std::string(multiple.begin(), multiple.begin() + mid),
        std::string(multiple.begin() + mid, multiple.end())};

    std::pair<std::string, std::string> high_low_2 = {
        std::string(multiplier.begin(), multiplier.begin() + mid),
        std::string(multiplier.begin() + mid, multiplier.end())};

    std::string z0 = karatsuba_multiply(high_low_1.second, high_low_1.second);
    std::string z1 = karatsuba_multiply(helper_adder(high_low_1.second, high_low_1.first), helper_adder(high_low_2.second, high_low_1.first));
    std::string z2 = karatsuba_multiply(high_low_1.first, high_low_2.first);

    // (z2 × 10 ^ (m2 × 2)) + ((z1 - z2 - z0) × 10 ^ m2) + z0
    std::string expression_1 = karatsuba_multiply(z2, std::to_string(pow(10, mid * 2)));
    std::string expression_2 = helper_subtractor(z1, z2);
    expression_2 = helper_subtractor(expression_2, z0);
    expression_2 = karatsuba_multiply(expression_2, std::to_string(pow(10, mid)));
    std::string answer = helper_adder(expression_1, expression_2);
    return helper_adder(answer, z0);
}

BigInt &BigInt::multiply(const BigInt &multiplier)
{
    m_is_negative = (m_is_negative && multiplier.m_is_negative) || (!m_is_negative && !multiplier.m_is_negative) ? false : true;
    m_value = karatsuba_multiply(m_value, multiplier.m_value);
    return *this;
}

//Operators

BigInt& BigInt::operator ++(int){
    auto num = 
}