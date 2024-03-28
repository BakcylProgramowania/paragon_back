#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <database/database.hpp>

using namespace ::testing;

TEST(DatabaseLogingTest, ExpectedValidLoginToWork) {
  bakcyl::database::Database database(
      "mongodb+srv://"
      "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/");
  EXPECT_FALSE(database.loginCheck("Lucy", "wrongPassword"));
  EXPECT_TRUE(database.loginCheck("utest", "uTest123"));
  EXPECT_TRUE(database.isThereUserWithThisID("6605b3d13431efc35a0d7cb7"));
}

TEST(DatabaseBalanceTest, ExpectedValidBalanceToWork) {
  bakcyl::database::Database database(
      "mongodb+srv://"
      "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/");
  EXPECT_TRUE(database.changeBalance("6605b3d13431efc35a0d7cb7", 10.00));
  EXPECT_EQ(database.getBalance("6605b3d13431efc35a0d7cb7"), 10.00);
  EXPECT_TRUE(database.changeBalance("6605b3d13431efc35a0d7cb7", 15.55));
  EXPECT_EQ(database.getBalance("6605b3d13431efc35a0d7cb7"), 15.55);
}