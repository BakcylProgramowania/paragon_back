#include "reciptOperations.hpp"

namespace bakcyl {
namespace core {

ReciptOperations::ReciptOperations(bakcyl::database::Database& db) : database(db) {}

std::vector<bakcyl::core::User> ReciptOperations::calculateReceipt(
    const std::vector<bakcyl::core::Item>& items) const {
  std::vector<bakcyl::core::User> users;

  for (const auto& item : items) {
    int cost = item.price * item.amount;
    bool foundEqualUserID = false;

    if (!database.isThereUserWithThisID(item.whoBuy))
      return {};
    
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
    database.changeBalance(user.userID, database.getBalance(user.userID) + user.price);
  }

  return users;
};

}
}

