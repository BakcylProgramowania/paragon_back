#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <database/database.cpp>

using namespace ::testing;

TEST(DatabaseLogingTest, ExpectedValidLoginToWork)
{
    EXPECT_FALSE(logInCheck("Lucy", "wrongPassword"));
    EXPECT_FALSE(logInCheck("nonExistingUser", "ycuL"));
    EXPECT_FALSE(logInCheck("nonExistingEmail@wrong.wrong", "ycuL"));
    EXPECT_TRUE(logInCheck("Lucy", "ycuL"));
    EXPECT_TRUE(logInCheck("lucy00@test.com", "ycuL"));
}


