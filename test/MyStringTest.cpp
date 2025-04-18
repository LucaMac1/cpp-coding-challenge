#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MyString.h"

TEST(MyStringTest, DefaultConstructorCreatesEmptyString)
{
    MyString s;
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_EQ(s.size(), 0);
}

TEST(MyStringTest, ConstructFromCString)
{
    MyString s("hello");
    EXPECT_STREQ(s.c_str(), "hello");
    EXPECT_EQ(s.size(), 5);
}

TEST(MyStringTest, CopyConstructorCreatesDeepCopy)
{
    MyString a("test");
    MyString b(a);
    EXPECT_STREQ(b.c_str(), "test");
    EXPECT_NE(a.c_str(), b.c_str());
}

TEST(MyStringTest, CopyAssignmentPerformsDeepCopy)
{
    MyString a("alpha");
    MyString b("beta");
    b = a;
    EXPECT_STREQ(b.c_str(), "alpha");
    EXPECT_NE(a.c_str(), b.c_str());
}

TEST(MyStringTest, MoveConstructorTransfersOwnership)
{
    MyString a("moved");
    const char *original_ptr = a.c_str();
    MyString b(std::move(a));
    EXPECT_STREQ(b.c_str(), "moved");
    EXPECT_EQ(a.c_str(), nullptr);
    EXPECT_EQ(b.c_str(), original_ptr);
}

TEST(MyStringTest, MoveAssignmentTransfersOwnership)
{
    MyString a("alpha");
    MyString b("beta");
    b = std::move(a);
    EXPECT_STREQ(b.c_str(), "alpha");
    EXPECT_EQ(a.c_str(), nullptr);
}

TEST(MyStringTest, EqualityComparison)
{
    MyString a("abc");
    MyString b("abc");
    MyString c("def");

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(MyStringTest, ConcatenationOperator)
{
    MyString a("hello");
    MyString b("world");
    MyString c = a + b;
    EXPECT_STREQ(c.c_str(), "helloworld");
}