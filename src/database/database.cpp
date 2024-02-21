#include "database.hpp"

#include "databaseImpl.hpp"

Database::Database(const std::string& address)
    : impl(new DatabaseImpl(address)){};
Database::~Database() = default;

bool Database::createUser(const std::string& username,
                          const std::string& password, const std::string& email,
                          const std::string& token) {
  return impl->createUser(username, password, email, token);
}

bool Database::deleteUser(const std::string& id, const std::string& password) {
  return impl->deleteUser(id, password);
}

bool Database::loginCheck(const std::string& id,
                          const std::string& password) const {
  return impl->loginCheck(id, password);
}

std::string Database::getToken(const std::string& username,
                               const std::string& password) const {
  return impl->getToken(username, password);
}

bool Database::tokenCheck(const std::string& token) const {
  return impl->tokenCheck(token);
}

bool Database::changeBalance(const std::string& userID, double amount) {
  return impl->changeBalance(userID, amount);
}

double Database::getBalance(const std::string& token) const {
  return impl->getBalance(token);
}

std::vector<std::pair<std::string, std::string>>
Database::returnUserFriendList(const std::string& userID) const {
  return impl->returnUserFriendList(userID);
}

bool Database::addUserToFriendList(const std::string& token, const std::string& friendIdToAdd) const{
  return impl->addUserToFriendList(token, friendIdToAdd);
}

bool Database::removeUserFromFriendList(const std::string& token, const std::string& friendIdToRemove) const{
  return impl->removeUserFromFriendList(token, friendIdToRemove);
}

std::string Database::getUserIDUsingToken(const std::string& token) const{
  return impl->getUserIDUsingToken(token);
}