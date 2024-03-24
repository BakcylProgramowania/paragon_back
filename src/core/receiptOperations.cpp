#include "receiptOperations.hpp"

namespace bakcyl {
namespace core {

ReceiptOperations::ReceiptOperations(bakcyl::database::Database& db)
    : database(db) {}

std::vector<bakcyl::core::User> ReceiptOperations::calculateReceipt(
    const std::vector<bakcyl::core::Item>& items) const {
  std::vector<bakcyl::core::User> users;

  for (const auto& item : items) {
    double cost = floor((item.price * item.amount) * 1000) / 1000;

    bool foundEqualUserID = false;

    if (!database.isThereUserWithThisID(item.whoBuy)) return {};
    
    for (auto& user : users) {
      if (user.userID == item.whoBuy) {
        user.price += cost;
        foundEqualUserID = true;
        break;
      }
    }

    if (!foundEqualUserID) {
      bakcyl::core::User user = {item.whoBuy, cost};
      users.push_back(user);
    }
  }

  for (const auto& user : users) {
    database.changeBalance(user.userID,
                           database.getBalance(user.userID) + user.price);
  }

  return users;
};

int ReceiptOperations::saveReceipt(bakcyl::core::Receipt& receipt) const {
  std::vector<std::string> usersIncluded;
  
  receipt.date = std::to_string(time(0));
  for (auto& item : receipt.items) {
    item.price = item.price * item.amount;
    item.amount = 0;

    bool found = false;
    for(const auto& user : usersIncluded) {
      if(user == item.whoBuy) {
        found = true;
        break;
      }
    }
    if(!found)
      usersIncluded.push_back(item.whoBuy);
  }
  receipt.usersIncluded = usersIncluded;
  return database.createReceiptInHistory(receipt);
};

std::vector<bakcyl::core::ReceiptShortView> ReceiptOperations::getReceipts(const std::string& token) {
  return database.getReceipts(database.getUserIDUsingToken(token));
};

}  // namespace core
}  // namespace bakcyl