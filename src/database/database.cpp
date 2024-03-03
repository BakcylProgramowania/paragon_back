#include "database.hpp"

#include "databaseImpl.hpp"

namespace bakcyl {
namespace database {

Database::Database(const std::string& address)
    : impl(new DatabaseImpl(address)){};
Database::~Database() = default;

bool bakcyl::database::Database::createUser(const std::string& username,
                          const std::string& password, const std::string& email,
                          const std::string& token) {
  return bakcyl::database::Database::impl->createUser(username, password, email, token);
}

bool bakcyl::database::Database::deleteUser(const std::string& id, const std::string& password) {
  return bakcyl::database::Database::impl->deleteUser(id, password);
}

bool bakcyl::database::Database::loginCheck(const std::string& id,
                          const std::string& password) const {
  return bakcyl::database::Database::impl->loginCheck(id, password);
}

std::string bakcyl::database::Database::getToken(const std::string& username,
                               const std::string& password) const {
  return bakcyl::database::Database::impl->getToken(username, password);
}

bool bakcyl::database::Database::tokenCheck(const std::string& token) const {
  return bakcyl::database::Database::impl->tokenCheck(token);
}

bool bakcyl::database::Database::changeBalance(const std::string& userID, double amount) {
  return bakcyl::database::Database::impl->changeBalance(userID, amount);
}

double bakcyl::database::Database::getBalance(const std::string& userID) const {
  return bakcyl::database::Database::impl->getBalance(userID);
}

std::vector<std::pair<std::string, std::string>> bakcyl::database::Database::returnUserFriendList(
    const std::string& userID) const {
  return bakcyl::database::Database::impl->returnUserFriendList(userID);
}

bool bakcyl::database::Database::addUserToFriendList(const std::string& token,
                                   const std::string& friendIdToAdd) const {
  return bakcyl::database::Database::impl->addUserToFriendList(token, friendIdToAdd);
}

bool bakcyl::database::Database::removeUserFromFriendList(
    const std::string& token, const std::string& friendIdToRemove) const {
  return bakcyl::database::Database::impl->removeUserFromFriendList(token, friendIdToRemove);
}

std::string bakcyl::database::Database::getUserIDUsingToken(const std::string& token) const {
  return bakcyl::database::Database::impl->getUserIDUsingToken(token);
}

}
}