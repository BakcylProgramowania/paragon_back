#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <database/database.cpp>

using namespace ::testing;

TEST(DatabaseLogingTest, ExpectedValidLoginToWork)
{
    Database database;
    EXPECT_FALSE(database.logInCheck("Lucy", "wrongPassword"));
    EXPECT_FALSE(database.logInCheck("nonExistingUser", "ycuL"));
    EXPECT_FALSE(database.logInCheck("nonExistingEmail@wrong.wrong", "ycuL"));
    EXPECT_TRUE(database.logInCheck("Lucy", "ycuL"));
    EXPECT_TRUE(database.logInCheck("lucy00@test.com", "ycuL"));
}


