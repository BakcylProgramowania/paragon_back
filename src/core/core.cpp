#include "core.hpp"

#include <nlohmann/json.hpp>
#include <string>
#include <vector>
using json = nlohmann::json;

std::vector<Product> getProducts(const json& jsonData) {
  std::vector<Product> products;

  if (jsonData.contains("receipt")) {
    for (const auto& receiptData : jsonData["receipt"]) {
      if (!receiptData.contains("products")) {
        continue;  // Skip this iteration and proceed to the next
      }

      for (const auto& productData : receiptData["products"]) {
        Product product;

        if (productData.contains("product")) {
          product.name = productData["product"];
        }

        if (productData.contains("amount")) {
          product.amount = productData["amount"];
        }

        if (productData.contains("price")) {
          product.price = productData["price"];
        }

        if (productData.contains("whoBought")) {
          if (productData["whoBought"].is_object()) {
            if (productData["whoBought"].contains("personID")) {
              product.whoBoughtID = productData["whoBought"]["personID"];
            } else {
              continue;
            }
          }
        }

        products.push_back(product);
      }
    }
  }

  return products;
}

std::vector<User> getUsers(const json& jsonData) {
  std::vector<User> users;

  if (jsonData.contains("users")) {
    for (const auto& userData : jsonData["users"]) {
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

  return users;
}

bool Authenticator::authenticateUser(const std::string& username, const std::string& password) const {
  return username == "Jan34";
}