#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <database/database.hpp>

using namespace ::testing;

TEST(DatabaseLogingTest, ExpectedValidLoginToWork)
{
    Database database("mongodb+srv://bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/");
    EXPECT_FALSE(database.loginCheck("Lucy", "wrongPassword"));
    EXPECT_FALSE(database.loginCheck("nonExistingUser", "ycuL"));
    EXPECT_FALSE(database.loginCheck("nonExistingEmail@wrong.wrong", "ycuL"));
    EXPECT_TRUE(database.loginCheck("Lucy", "ycuL"));
    EXPECT_TRUE(database.loginCheck("lucy00@test.com", "ycuL"));
}


