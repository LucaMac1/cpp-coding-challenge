#pragma once
#include <cstddef>

/// @class MyString
/// @brief A simple string class that mimics basic string operations like copy, move,
///        concatenation, and comparison.
class MyString
{
public:
    /// @brief Default Constructor that initializes an empty string.
    MyString();

    /// @brief Constructs a MyString object from a C-string.
    /// @param str A null-terminated C-string to initialize the MyString object.
    MyString(const char *str);

    /// @brief Copy Constructor that creates a deep copy of another MyString object.
    /// @param str The MyString object to copy from.
    MyString(const MyString &str);

    /// @brief Move Constructor that transfers ownership of the resources from another MyString object.
    /// @param str The MyString object to move from.
    /// @note This operation is noexcept and should not throw exceptions.
    MyString(MyString &&str) noexcept;

    /// @brief Copy Assignment Operator that performs a deep copy of another MyString object.
    /// @param str The MyString object to assign.
    /// @return A reference to the current MyString object.
    MyString &operator=(const MyString &str);

    /// @brief Move Assignment Operator that transfers ownership of the resources from another MyString object.
    /// @param str The MyString object to move from.
    /// @return A reference to the current MyString object.
    /// @note This operation is noexcept and should not throw exceptions.
    MyString &operator=(MyString &&str) noexcept;

    /// @brief Destructor that deallocates the dynamically allocated memory.
    ~MyString();

    /// @brief Accessor method to get the C-string representation of the string.
    /// @return A const pointer to the null-terminated C-string.
    const char *c_str() const;

    /// @brief Returns the size of the string (the number of characters).
    /// @return The size of the string.
    size_t size() const;

    /// @brief Equality comparison operator that compares two MyString objects.
    /// @param other The MyString object to compare with.
    /// @return true if both MyString objects are equal, false otherwise.
    bool operator==(const MyString &other) const;

    /// @brief Concatenation operator that combines two MyString objects into a new MyString.
    /// @param other The MyString object to concatenate with.
    /// @return A new MyString that is the concatenation of the current object and `other`.
    MyString operator+(const MyString &other) const;

private:
    char *m_data;  ///< Pointer to the dynamically allocated C-string data.
    size_t m_size; ///< The length (size) of the string.
};