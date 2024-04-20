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

TEST(DatabaseFriendsTest, ExpectedFriendsToWork) {
  bakcyl::database::Database database(
      "mongodb+srv://"
      "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/");

  EXPECT_TRUE(database.addUserToFriendList("6605b3d13431efc35a0d7cb7", "utestfriend"));

  EXPECT_FALSE(database.addUserToFriendList("6605b3d13431efc35a0d7cb7", "utestfriend"));

  std::vector<std::pair<std::string, std::string>> friendList = {{"660692a0a1a7a813cd0a51f1", "utestfriend"}};
  EXPECT_EQ(database.returnUserFriendList("6605b3d13431efc35a0d7cb7"), friendList);
  std::vector<std::pair<std::string, std::string>> friendList2 = {{"6605b3d13431efc35a0d7cb7", "utest"}};
  EXPECT_EQ(databse.returnUserFriendList("660692a0a1a7a813cd0a51f1", friendList2));

  EXPECT_TRUE(database.addUserToFriendList("6605b3d13431efc35a0d7cb7", "utestfriend2"));

  friendList = {{"660692a0a1a7a813cd0a51f1", "utestfriend"}, {"66069ed9313b82f91401a961", "utestfriend2"}};
  EXPECT_EQ(database.returnUserFriendList("6605b3d13431efc35a0d7cb7"), friendList);

  EXPECT_TRUE(database.removeUserFromFriendList("6605b3d13431efc35a0d7cb7", "utestfriend"));
  EXPECT_TRUE(database.removeUserFromFriendList("6605b3d13431efc35a0d7cb7", "utestfriend2"));

  EXPECT_FALSE(database.removeUserFromFriendList("6605b3d13431efc35a0d7cb7", "utestfriend"));
  EXPECT_FALSE(database.removeUserFromFriendList("6605b3d13431efc35a0d7cb7", "utestfriend2"));
  
  friendList.clear();
  friendList2.clear();
  EXPECT_EQ(database.returnUserFriendList("6605b3d13431efc35a0d7cb7"), friendList);
  EXPECT_EQ(database.returnUserFriendList("660692a0a1a7a813cd0a51f1"), friendList2);
}

TEST(DatabaseManagingUsersTest, ExpectedCreatingDeletingUsersToWork) {
  bakcyl::database::Database database(
      "mongodb+srv://"
      "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/");
  EXPECT_TRUE(database.createUser("utestNewUser", "utestNewUserPass", "utestNewUser@notExistingEmail.com", "utestNewUserRandomToken" ));
  EXPECT_FALSE(database.createUser("utestNewUser", "utestNewUserPass", "utestNewUser@notExistingEmail.com", "utestNewUserRandomToken" ));
  EXPECT_FALSE(database.createUser("utestNewUser", "utestNewUserPass", "utestNewUser@notExistingEmail.com2", "utestNewUserRandomToken" ));
  EXPECT_FALSE(database.createUser("utestNewUser2", "utestNewUserPass", "utestNewUser@notExistingEmail.com", "utestNewUserRandomToken" ));

  EXPECT_EQ(detabase.getToken("utestNewUser", "utestNewUserPass", "utestNewUserRandomToken"));
  
  EXPECT_EQ(detabase.getgetUserIDUsingToken("utestNewUserRandomToken"), database.getUserIDUsingUsername("utestNewUser"));
  
  EXPECT_TRUE(database.deleteUser("utestNewUser", "utestNewUserPass"));
  EXPECT_FALSE(database.deleteUser("utestNewUser", "utestNewUserPass"));
}