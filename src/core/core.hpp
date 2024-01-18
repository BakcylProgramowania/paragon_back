#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

namespace bakcyl {
namespace core {

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

std::vector<Product> getProducts(const json& jsonData);

std::vector<User> getUsers(const json& jsonData);

}  // namespace core
}  // namespace bakcyl