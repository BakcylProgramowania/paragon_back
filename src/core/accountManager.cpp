#include "accountManager.hpp"

namespace bakcyl {
namespace core {

AccountManager::AccountManager(bakcyl::database::Database& db)
    : database(db) {}  // Update constructor

bool AccountManager::changeBalance(const std::string& token, double amount) {
  return database.changeBalance(database.getUserIDUsingToken(token), amount);
}

double AccountManager::getBalance(const std::string& token) const {
  return database.getBalance(database.getUserIDUsingToken(token));
}

std::vector<std::pair<std::string, std::string>>
AccountManager::returnUserFriendList(const std::string& token) const {
  return database.returnUserFriendList(database.getUserIDUsingToken(token));
}

bool AccountManager::addUserToFriendList(
    const std::string& token, const std::string& friendUsernameToAdd) const {
  return database.addUserToFriendList(database.getUserIDUsingToken(token),
                                      friendUsernameToAdd);
}
bool AccountManager::removeUserFromFriendList(
    const std::string& token, const std::string& friendIdUsernameRemove) const {
  return database.removeUserFromFriendList(database.getUserIDUsingToken(token),
                                           friendIdUsernameRemove);
}

}
}