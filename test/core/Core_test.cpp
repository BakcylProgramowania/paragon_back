#include <gtest/gtest.h>
#include<core.cpp>
TEST(ParseJsonDataTest, ParsesJsonDataCorrectly) 
{
    // Arrange
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

    ASSERT_EQ(expectedProducts, actualProducts);
    ASSERT_EQ(expectedUsers, actualUsers);
}
