#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <database/database.hpp>

using namespace ::testing;

TEST(DatabaseLogingTest, ExpectedValidLoginToWork) {
  Database database(
      "mongodb+srv://"
      "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/");
  EXPECT_FALSE(database.loginCheck("Lucy", "wrongPassword"));
  EXPECT_FALSE(database.loginCheck("nonExistingUser", "ycuL"));
  EXPECT_FALSE(database.loginCheck("nonExistingEmail@wrong.wrong", "ycuL"));
  EXPECT_TRUE(database.loginCheck("Lucy", "ycuL"));
  EXPECT_TRUE(database.loginCheck("lucy00@test.com", "ycuL"));
}

TEST(DatabaseBalanceTest, ExpectedValidBalanceToWork) {
  Database database(
      "mongodb+srv://"
      "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/");
  EXPECT_TRUE(database.changeBalance("1a3d281d-64ae-47e0-8971-56720375a3d7", 0.00));
  EXPECT_EQ(database.getBalance("1a3d281d-64ae-47e0-8971-56720375a3d7"), 0.00);
  EXPECT_TRUE(database.changeBalance("1a3d281d-64ae-47e0-8971-56720375a3d7", 15.55));
  EXPECT_EQ(database.getBalance("1a3d281d-64ae-47e0-8971-56720375a3d7"), 15.55);
}