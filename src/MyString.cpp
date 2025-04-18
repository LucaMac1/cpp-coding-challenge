#include "MyString.h"
#include <iostream>
#include <cstring>

MyString::MyString() : m_size(0)
{
    std::cout << "[Default Constructor]" << std::endl;
    m_data = new char[1];
    m_data[0] = '\0';
}

MyString::~MyString()
{
    std::cout << "[Destructor]" << std::endl;
    if (m_data)
    {
        delete[] m_data;
    }
}

const char *MyString::c_str() const
{
    return this->m_data;
}

size_t MyString::size() const
{
    return this->m_size;
}

MyString::MyString(const char *str)
{
    std::cout << "[Constructor from const char*]" << std::endl;
    m_size = strlen(str);
    m_data = new char[m_size + 1];
    memcpy(m_data, str, m_size + 1);
}

MyString::MyString(const MyString &str)
{
    std::cout << "[Copy Constructor]" << std::endl;
    m_size = str.m_size;
    m_data = new char[m_size + 1];
    memcpy(m_data, str.m_data, m_size + 1);
}

MyString::MyString(MyString &&str) noexcept
{
    std::cout << "[Move Constructor]" << std::endl;
    m_size = str.m_size;
    m_data = str.m_data;

    str.m_data = nullptr;
    str.m_size = 0;
}

MyString &MyString::operator=(const MyString &str)
{
    std::cout << "[Copy Assignment Operator]" << std::endl;

    // Self-assignment guard
    if (this == &str)
        return *this;

    delete[] m_data;

    m_size = str.m_size;
    m_data = new char[m_size + 1];
    std::memcpy(m_data, str.m_data, m_size + 1);

    return *this;
}

MyString &MyString::operator=(MyString &&str) noexcept
{
    std::cout << "[Move Assignment Operator]" << std::endl;

    m_size = str.m_size;
    m_data = str.m_data;

    str.m_data = nullptr;
    str.m_size = 0;

    return *this;
}

bool MyString::operator==(const MyString &other) const
{
    if (m_size != other.m_size)
        return false;

    return std::strncmp(m_data, other.m_data, m_size) == 0;
}

MyString MyString::operator+(const MyString &other) const
{
    size_t newSize = m_size + other.m_size;
    char *newData = new char[newSize + 1];

    std::memcpy(newData, m_data, m_size);
    std::memcpy(newData + m_size, other.m_data, other.m_size);
    newData[newSize] = '\0';

    MyString result(newData);
    delete[] newData;
    return result;
}