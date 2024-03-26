#pragma once
#include "core/structures.hpp"

#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
#include <utility>
#include <vector>

namespace bakcyl {
namespace database {

class DatabaseImpl {
 public:
  DatabaseImpl(const std::string& address);
  ~DatabaseImpl() = default;
  bool createUser(const std::string& username, const std::string& password,
                  const std::string& email, const std::string& token);
  bool deleteUser(const std::string& id, const std::string& password);
  bool loginCheck(const std::string& id, const std::string& password) const;
  std::string getToken(const std::string& username,
                       const std::string& password);
  bool tokenCheck(const std::string& token) const;
  bool changeBalance(const std::string& userID, double amount);
  double getBalance(const std::string& userID) const;

  std::vector<std::pair<std::string, std::string>> returnUserFriendList(
      const std::string& userID) const;
  bool addUserToFriendList(const std::string& userID,
                           const std::string& friendIdToAdd) const;
  bool removeUserFromFriendList(const std::string& userID,
                                const std::string& friendIdToRemove) const;
  std::string getUserIDUsingToken(const std::string& token) const;
  bool isThereUserWithThisID(const std::string& userID) const;
  int createReceiptInHistory(const bakcyl::core::Receipt& receipt);
  bakcyl::core::Receipt getReceipt(const std::string& receiptID);
  bool changeIfMerged(const std::string& receiptID, const bool& newState);
  std::vector<bakcyl::core::ReceiptShortView> getReceipts(const std::string& userID);
  bool paidForItem(const std::string& receiptID, const std::string& itemName, const std::string& whoBuy);
 private:
  bool isUserPasswordEqualGivenPassword(mongocxx::cursor& cursor,
                                        const std::string& password) const;
  bool isThereUserWithThisUsername(const std::string& username) const;
  bool isThereUserWithThisEmail(const std::string& email) const;

  mongocxx::uri uri;
  mongocxx::client client;
  mongocxx::database database;
};

}
}