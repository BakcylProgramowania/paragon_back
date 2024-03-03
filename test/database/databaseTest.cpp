#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <database/database.hpp>

using namespace ::testing;

TEST(DatabaseLogingTest, ExpectedValidLoginToWork) {
  bakcyl::database::Database database(
      "mongodb+srv://"
      "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/");
  EXPECT_FALSE(database.loginCheck("Lucy", "wrongPassword"));
  EXPECT_FALSE(database.loginCheck("nonExistingUser", "ycuL"));
  EXPECT_FALSE(database.loginCheck("nonExistingEmail@wrong.wrong", "ycuL"));
  EXPECT_TRUE(database.loginCheck("Lucy", "ycuL"));
  EXPECT_TRUE(database.loginCheck("lucy00@test.com", "ycuL"));
}

TEST(DatabaseBalanceTest, ExpectedValidBalanceToWork) {
  bakcyl::database::Database database(
      "mongodb+srv://"
      "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/");
  EXPECT_TRUE(database.changeBalance("65b3c6e05cf3bd901c04aa52", 0.00));
  EXPECT_EQ(database.getBalance("65b3c6e05cf3bd901c04aa52"), 0.00);
  EXPECT_TRUE(database.changeBalance("65b3c6e05cf3bd901c04aa52", 15.55));
  EXPECT_EQ(database.getBalance("65b3c6e05cf3bd901c04aa52"), 15.55);
}