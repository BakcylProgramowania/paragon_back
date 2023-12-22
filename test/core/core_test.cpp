#include <gtest/gtest.h>
#include "core/core.hpp"

TEST(GetProductsTest, RetrievesProductsCorrectly) 
{
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
    
    const std::vector<Product> expectProducts = 
    {
        {"Item1", 10.5, 2, 1},
        {"Item2", 5.99, 1, 2}
    };
    
    const std::vector<Product> actualProducts = getProducts(jsonData);
    ASSERT_EQ(actualProducts, expectProducts);
}

TEST(GetUsersTest, RetrievesUsersCorrectly) 
{
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

    const std::vector<User> expectUsers = 
    {
        {"John Doe", "123-456-7890", 1},
        {"Jane Doe", "987-654-3210", 2}
    };

    const std::vector<User> actualUsers = getUsers(jsonData);
    ASSERT_EQ(actualUsers, expectUsers);
}
