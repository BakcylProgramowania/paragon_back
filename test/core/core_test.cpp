#include <gtest/gtest.h>
#include "core/core.cpp"

    const std::string jsonInput = R"(
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
            ],
            "users": [
                {
                    "id": 1,
                    "name": "Wladek Mandziuk",
                    "phone": "123-456-7890"
                },
                {
                    "id": 2,
                    "name": "Michal Jakistam",
                    "phone": "987-654-3210"
                }
            ]
        }
    )";

TEST(ParseJsonDataTest, ParsesJsonDataCorrectly) 
{

    json jsonData = json::parse(jsonInput);

    std::vector<Product> expectedProducts = {
        {"Item1", 10.5, 2, 1},
        {"Item2", 5.99, 1, 2}
    };

    std::vector<User> expectedUsers = {
        {"Wladek Mandziuk", "123-456-7890", 1},
        {"Michal Jakistam", "987-654-3210", 2}
    };

    std::vector<Product> actualProducts;
    std::vector<User> actualUsers;

      parseJsonData(jsonData, actualProducts, actualUsers);

EXPECT_EQ(actualProducts.size(), expectedProducts.size());
for (size_t i = 0; i < actualProducts.size(); ++i) 
{
    EXPECT_EQ(actualProducts[i].name, expectedProducts[i].name);
    EXPECT_EQ(actualProducts[i].price, expectedProducts[i].price);
    EXPECT_EQ(actualProducts[i].amount, expectedProducts[i].amount);
    EXPECT_EQ(actualProducts[i].whoBoughtID, expectedProducts[i].whoBoughtID);
}

EXPECT_EQ(actualUsers.size(), expectedUsers.size());
for (size_t i = 0; i < actualUsers.size(); ++i)
{
    EXPECT_EQ(actualUsers[i].name, expectedUsers[i].name);
    EXPECT_EQ(actualUsers[i].phone, expectedUsers[i].phone);
    EXPECT_EQ(actualUsers[i].id, expectedUsers[i].id);
}

    
}
