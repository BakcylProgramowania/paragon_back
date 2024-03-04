#include <gtest/gtest.h>

#include "core/authenticator.hpp"

TEST(WhetherUserIsCorrect, ReturnTrueForUserJan34) {
  bakcyl::database::Database database(
      "mongodb+srv://"
      "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/");
  bakcyl::core::Authenticator auth(database);
  EXPECT_FALSE(auth.authenticateUser("Jan34", "Jan905").empty());
}
