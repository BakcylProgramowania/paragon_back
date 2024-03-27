#pragma once

#include "database/database.hpp"

namespace bakcyl {
namespace core {

class AccountManager {
  bakcyl::database::Database& database;

 public:
  AccountManager(bakcyl::database::Database& db);

  bool changeBalance(const std::string& token, double amount);
  double getBalance(const std::string& token) const;
  std::vector<std::pair<std::string, std::string>> returnUserFriendList(
      const std::string& token) const;
  bool addUserToFriendList(const std::string& token,
                           const std::string& friendUsernameToAdd) const;
  bool removeUserFromFriendList(const std::string& token,
                                const std::string& friendUsernameToRemove) const;
};

}
}