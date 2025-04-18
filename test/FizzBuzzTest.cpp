/*
Problem: Write a function std::string fizzbuzz(int n) that:

Returns "Fizz" if the number is divisible by 3.

Returns "Buzz" if the number is divisible by 5.

Returns "FizzBuzz" if divisible by both 3 and 5.

Otherwise, returns the number as a string.

TDD Focus:

Start with the smallest test case (fizzbuzz(1) → "1"), write a failing test, then make it pass.

Incrementally build up the logic.
*/


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FizzBuzz.h"

// TEST(FizzBuzzFunctionTest, HandlesNonFizzBuzz)
// {
//     std::string result = fizzbuzz(1);
//     ASSERT_EQ(result, std::to_string(1));
// }

// TEST(FizzBuzzFunctionTest, HandleFizzOnly)
// {
//     std::string result = fizzbuzz(6);
//     ASSERT_EQ(result, "Fizz");
// }

// TEST(FizzBuzzFunctionTest, HandleBuzzOnly)
// {
//     std::string result = fizzbuzz(10);
//     ASSERT_EQ(result, "Buzz");
// }

// TEST(FizzBuzzFunctionTest, HandleFizzBuzz)
// {
//     std::string result = fizzbuzz(15);
//     ASSERT_EQ(result, "FizzBuzz");
// }

class FizzBuzzParamTest : public ::testing::TestWithParam<std::pair<int, std::string>> {};

TEST_P(FizzBuzzParamTest, ReturnsExpectedString)
{
    auto [input, expected] = GetParam();
    ASSERT_EQ(fizzbuzz(input), expected);
}

INSTANTIATE_TEST_SUITE_P(
    VariousCases,
    FizzBuzzParamTest,
    ::testing::Values(
        std::make_pair(1, "1"),
        std::make_pair(2, "2"),
        std::make_pair(3, "Fizz"),
        std::make_pair(5, "Buzz"),
        std::make_pair(15, "FizzBuzz"),
        std::make_pair(30, "FizzBuzz")
    )
);
