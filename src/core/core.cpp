#include <vector>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;


struct Product 
{
    std::string name;
    double price;
    int amount;
    int whoBoughtID;
};

struct User 
{
    std::string name;
    std::string phone;
    int id;
};

void parseJsonData(const json& jsonData, std::vector<Product>& products, std::vector<User>& users) 
{
    if (jsonData.contains("receipt")) 
    {
        for (const auto& receiptData : jsonData["receipt"]) 
        {
            if (!receiptData.contains("products"))
            {
                continue;  // Skip this iteration and proceed to the next
            }

            for (const auto& productData : receiptData["products"]) 
            {
                Product product;

                if (productData.contains("product"))
                {
                    product.name = productData["product"];
                }

                if (productData.contains("amount")) 
                {
                    product.amount = productData["amount"];
                }

                if (productData.contains("price")) 
                {
                    product.price = productData["price"];
                }

                if (productData.contains("whoBought"))
                {
                    if (productData["whoBought"].is_object())
                    {
                        if (productData["whoBought"].contains("personID"))
                        {
                            product.whoBoughtID = productData["whoBought"]["personID"];
                        } 
                        else
                        {
                           continue;
                        }
                    }
                }

                products.push_back(product);
            }
        }
    }

    if (jsonData.contains("users")) {
        for (const auto& userData : jsonData["users"]) 
        {
            User user;

            if (userData.contains("id")) {
                user.id = userData["id"];
            }

            if (userData.contains("name")) {
                user.name = userData["name"];
            }

            if (userData.contains("phone")) {
                user.phone = userData["phone"];
            }

            users.push_back(user);
        }
    }
}

int main() 
{
    
    std::vector<Product> products;
    std::vector<User> users;
    std::string jsonData;
    
   json parsedData = json::parse(jsonData);

    parseJsonData(parsedData, products, users);
    
    }
  

   
    return 0;
}
