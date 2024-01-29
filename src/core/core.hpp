#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

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

class Data {
 public:
  std::vector<Product> getProducts(const json& jsonData) const;
  std::vector<User> getUsers(const json& jsonData) const;
};