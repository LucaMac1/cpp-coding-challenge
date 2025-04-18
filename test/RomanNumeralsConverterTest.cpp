/*
Convert an integer to its Roman numeral representation 
(e.g., 4 -> "IV", 9 -> "IX", 58 -> "LVIII", 1994 -> "MCMXCIV"). 
Only valid for 1 <= number <= 3999.

TDD Challenge
*/


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "RomanNumeralsConverter.h"

class RomanNumeralsConverterFunctionTest : public ::testing::TestWithParam<std::pair<int, std::string>> {};

TEST_P(RomanNumeralsConverterFunctionTest, ReturnsExpectedString)
{
    auto [input, expected] = GetParam();
    ASSERT_EQ(intToRoman(input), expected);
}

INSTANTIATE_TEST_SUITE_P(
    VariousCases,
    RomanNumeralsConverterFunctionTest,
    ::testing::Values(
        std::make_pair(1, "I"),
        std::make_pair(5, "V"),
        std::make_pair(10, "X"),
        std::make_pair(50, "L"),
        std::make_pair(100, "C"),
        std::make_pair(1000, "M"),
        std::make_pair(2, "II"),
        std::make_pair(4, "IV"),
        std::make_pair(9, "IX"),
        std::make_pair(58, "LVIII"),     // L = 50, V = 5, III = 3
        std::make_pair(1994, "MCMXCIV")  // M=1000, CM=900, XC=90, IV=4
    )
);