#include <gtest/gtest.h>
#include "core/core.cpp"
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

    std::cout << "Parsed Products:" << std::endl;
    for (const auto& product : actualProducts) {
        std::cout << product.name << ", " << product.price << ", " << product.amount << ", " << product.whoBoughtID << std::endl;
    }

    std::cout << "Parsed Users:" << std::endl;
    for (const auto& user : actualUsers) {
        std::cout << user.name << ", " << user.phone << ", " << user.id << std::endl;
    }

    ASSERT_THAT(actualProducts, testing::ElementsAreArray(expectedProducts));
    ASSERT_THAT(actualUsers, testing::ElementsAreArray(expectedUsers));
}
