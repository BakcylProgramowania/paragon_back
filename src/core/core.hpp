#pragma once

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

void parseJsonData(const json& jsonData, std::vector<Product>& products, std::vector<User>& users);
