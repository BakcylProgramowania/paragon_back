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
int main() {
    std::vector<Product> products;
    std::vector<User> users;
  
  std::string jsonData = "
  {"receipt":[{"products":[{"product":"sth","amount":sth,"price":sth,"whoBought",{"personiD":sth,
"personID":sth}]},
  {"product":"sth","amount":sth,"price":sth,"whoBought":2}]}],
"users":[{id":1,"name":"sth","phone":"sth"},
  {"id":2,"name":"sth","phone":"sth"}]}";"
    
     json parsedData = json::parse(jsonData);
    
    for (const auto& productData : parsedData["products"]) {
        Product product;
        product.name = productData["name"];
        product.amount = productData["amount"];
        product.price = productData["price"];
        product.whoBoughtID = productData["whoBoughtID"];
        products.push_back(product);
    }

    for (const auto& userData : parsedData["users"]) {
        User user;
        user.id = userData["id"];
        user.name = userData["name"];
        user.phone = userData["phone"];
        users.push_back(user);
    }
  

   
    return 0;
}
