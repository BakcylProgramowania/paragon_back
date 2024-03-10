#pragma once
#include <string>
#include <vector>

namespace bakcyl {
namespace core {

struct User {
  std::string userID;
  int price;
};

struct Item {
  std::string whoBuy;
  std::string itemName;
  int price;
  int amount;
};

struct Receipt {
    std::string author;
    std::vector<std::string> usersIncluded;
    std::string receiptName;
    std::string date;
    std::vector<bakcyl::core::Item> items;
};

}
}