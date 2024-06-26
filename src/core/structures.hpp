#pragma once
#include <string>
#include <vector>

namespace bakcyl {
namespace core {

struct User {
  std::string userID;
  double price;
};

struct Item {
  std::string whoBuy;
  std::string itemName;
  double price;
  double amount;
  bool paid;
};

struct Receipt {
  std::string author;
  std::vector<std::string> usersIncluded;
  std::string receiptName;
  std::string date;
  std::vector<bakcyl::core::Item> items;
  std::vector<std::string> mergedReceipts;
};

struct ReceiptShortView {
  std::string receiptName;
  std::string receiptID;
};

struct ItemToPay {
  std::string receiptID;
  std::string itemName;
  float price;
};

}  // namespace core
}  // namespace bakcyl