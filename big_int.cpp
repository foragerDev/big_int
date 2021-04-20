#include <algorithm>
#include <stdexcept>
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
void BigInt::remove_lead_zeros(std::string &value)
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

BigInt &BigInt::add(const BigInt &num)
{   
    std::string temp;
    if((m_is_negative && num.m_is_negative) || (!m_is_negative && !num.m_is_negative)){
        int carry = 0;
        int index_a = m_value.length() - 1, index_b = m_value.length() - 1;
        while(index_a >= 0 || index_b >= 0 || carry){
            int current_sum = 0;
            if(index_a >= 0) current_sum += (m_value[index_a] - '0'), index_a--;
            if (index_b >= 0) current_sum += (num.m_value[index_b] - '0'), index_b--;
            current_sum += carry;
            temp += ((current_sum % 10) + '0');
            carry = (current_sum / 10); 
        }
        std::reverse(temp.begin(), temp.end());
        m_value = temp; 
    }
    return *this;
}
