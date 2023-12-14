#include <vector>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;


struct Product {
    std::string name;
    double price;
    int amount;
    int whoBoughtID;
};

struct User {
    std::string name;
    std::string phone;
    int id;
};

void parseJsonData(const json& jsonData, std::vector<Product>& products, std::vector<User>& users) {
    for (const auto& receiptData : jsonData["receipt"]) {
        for (const auto& productData : receiptData["products"]) {
            Product product;
            product.name = productData["product"];
            product.amount = productData["amount"];
            product.price = productData["price"];

            if (productData.contains("whoBought")) {
                product.whoBoughtID = productData["whoBought"]["personID"];
            } else {
                product.whoBoughtID = productData["whoBought"];
            }

            products.push_back(product);
        }
    }

    for (const auto& userData : jsonData["users"]) {
        User user;
        user.id = userData["id"];
        user.name = userData["name"];
        user.phone = userData["phone"];
        users.push_back(user);
    }
}

int main() {
    
    std::vector<Product> products;
    std::vector<User> users;
    std::string jsonData;
    
   json parsedData = json::parse(jsonData);

    parseJsonData(parsedData, products, users);
    }
  

   
    return 0;
}
