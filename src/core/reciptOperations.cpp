#include "reciptOperations.hpp"

ReciptOperations::ReciptOperations(Database& db) : database(db) {}

std::vector<User> ReciptOperations::calculateReceipt(
    const std::vector<Item>& items) const {
  std::vector<User> users;

  for (const auto& item : items) {
    int cost = item.price * item.amount;
    bool foundEqualUserID = false;

    if (!database.isThereUserWithThisID(item.whoBuy)) {
      std::vector<User> usersNull;
      return usersNull;
    }
    
    for (auto& user : users) {
      if (user.userID == item.whoBuy) {
        user.price += cost;
        foundEqualUserID = true;
        break;
      }
    }

    if (!foundEqualUserID) {
      User user = {item.whoBuy, cost};
      users.push_back(user);
    }
  }

  for (const auto& user : users) {
    database.changeBalance(user.userID, database.getBalance(user.userID) + user.price);
  }

  return users;
}
