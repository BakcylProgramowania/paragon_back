#pragma once
#include "core/structures.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace bakcyl {
namespace database {

class DatabaseImpl;

class Database {
 public:
  Database(const std::string& address);
  ~Database();

  bool createUser(const std::string& username, const std::string& password,
                  const std::string& email, const std::string& token);
  bool deleteUser(const std::string& id, const std::string& password);
  bool loginCheck(const std::string& id, const std::string& password) const;
  std::string getToken(const std::string& username,
                       const std::string& password) const;
  bool tokenCheck(const std::string& token) const;
  bool changeBalance(const std::string& userID, double amount);
  double getBalance(const std::string& userID) const;

  std::vector<std::pair<std::string, std::string>> returnUserFriendList(
      const std::string& userID) const;
  bool addUserToFriendList(const std::string& token,
                           const std::string& friendUsernameToAdd) const;
  bool removeUserFromFriendList(const std::string& token,
                                const std::string& friendUsernameToRemove) const;
  std::string getUserIDUsingToken(const std::string& token) const;
  bool isThereUserWithThisID(const std::string& userID) const;
  int createReceiptInHistory(const bakcyl::core::Receipt& receipt);
  bakcyl::core::Receipt getReceipt(const std::string& receiptID);
  bool changeIfMerged(const std::string& receiptID, const bool& newState);
  std::vector<bakcyl::core::ReceiptShortView> getReceipts(const std::string& userID);
  bool paidForItem(const std::string& receiptID, const std::string& itemName, const std::string& whoBuy);
  std::vector<bakcyl::core::ItemToPay> getItemsToPay(const std::string& userID);
  std::string getUserIDUsingUsername(const std::string& username) const;
  bool isThereUserWithThisUsername(const std::string& username) const;
 private:
  std::unique_ptr<DatabaseImpl> impl;
};

}
}