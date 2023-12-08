#include <iostream>
#include <vector>
#include "json.hpp"
#include <string>

using json = nlohmann::json;


struct Product {
    std::string name;
    int amount;
    double price;
    int whoBoughtID;
};

struct User {
    int id;
    std::string name;
    std::string phone;
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
    
      {"receipt":[{"products":[{"product":"sth","amount":sth,"price":sth,"whoBought",{"personiD":sth,"personID":sth}]},
      {"product":"sth","amount":sth,"price":sth,"whoBought":2}]}],
       "users":[{id":1,"name":"sth","phone":"sth"},
      {"id":2,"name":"sth","phone":"sth"}]}";
    
   json parsedData = json::parse(jsonData);

    parseJsonData(parsedData, products, users);
    }
  

   
    return 0;
}
