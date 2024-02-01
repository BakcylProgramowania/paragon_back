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

bool Database::changeBalance(const std::string& token, double amount) {
  return impl->changeBalance(token, amount);
}

double Database::getBalance(const std::string& token) const {
  return impl->getBalance(token);
}
