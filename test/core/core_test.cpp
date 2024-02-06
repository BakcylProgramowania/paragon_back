#include "core/core.hpp"

#include <gtest/gtest.h>

#include "core/authenticator.hpp"

TEST(GetProductsTest, RetrievesProductsCorrectly) {
  Data data;
  const json jsonData = R"(
        {
            "receipt": [
                {
                    "products": [
                        {
                            "product": "Item1",
                            "amount": 2,
                            "price": 10.5,
                            "whoBought": {
                                "personID": 1
                            }
                        },
                        {
                            "product": "Item2",
                            "amount": 1,
                            "price": 5.99,
                            "whoBought": {
                                "personID": 2
                            }
                        }
                    ]
                }
            ]
        }
    )"_json;

  const std::vector<Product> expectProducts = {{"Item1", 10.5, 2, 1},
                                               {"Item2", 5.99, 1, 2}};

  const std::vector<Product> actualProducts = data.getProducts(jsonData);

  EXPECT_EQ(actualProducts.size(), expectProducts.size());

  for (size_t i = 0; i < actualProducts.size(); ++i) {
    EXPECT_EQ(actualProducts[i].name, expectProducts[i].name);
    EXPECT_EQ(actualProducts[i].price, expectProducts[i].price);
    EXPECT_EQ(actualProducts[i].amount, expectProducts[i].amount);
    EXPECT_EQ(actualProducts[i].whoBoughtID, expectProducts[i].whoBoughtID);
  }
}

TEST(GetUsersTest, RetrievesUsersCorrectly) {
  Data data;
  const json jsonData = R"(
        {
            "users": [
                {
                    "id": 1,
                    "name": "John Doe",
                    "phone": "123-456-7890"
                },
                {
                    "id": 2,
                    "name": "Jane Doe",
                    "phone": "987-654-3210"
                }
            ]
        }
    )"_json;

  const std::vector<User> expectUsers = {{"John Doe", "123-456-7890", 1},
                                         {"Jane Doe", "987-654-3210", 2}};

  const std::vector<User> actualUsers = data.getUsers(jsonData);

  EXPECT_EQ(actualUsers.size(), expectUsers.size());

  for (size_t i = 0; i < actualUsers.size(); ++i) {
    EXPECT_EQ(actualUsers[i].name, expectUsers[i].name);
    EXPECT_EQ(actualUsers[i].phone, expectUsers[i].phone);
    EXPECT_EQ(actualUsers[i].id, expectUsers[i].id);
  }
}

TEST(WhetherUserIsCorrect, ReturnTrueForUserJan34) {
  Database database("mongodb+srv://"
          "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/")
  Authenticator auth(database);
  EXPECT_FALSE(auth.authenticateUser("Jan34", "Jan905").empty());
}
