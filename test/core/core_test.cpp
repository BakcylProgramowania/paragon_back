#include <gtest/gtest.h>
#include "core/core.hpp"

TEST(GetProductsTest, RetrievesProductsCorrectly) {

    json jsonData = R"(
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

    std::vector<Product> products = getProducts(jsonData);

    ASSERT_EQ(products.size(), 2);
}

TEST(GetUsersTest, RetrievesUsersCorrectly) {
    json jsonData = R"(
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
    
    std::vector<User> users = getUsers(jsonData);

    ASSERT_EQ(users.size(), 2);
}
