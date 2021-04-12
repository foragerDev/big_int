#include <algorithm>
#include <stdexcept>
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

bool BigInt::is_greater(const BigInt& other) const{
    
}