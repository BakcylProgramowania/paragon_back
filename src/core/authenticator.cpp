#include "authenticator.hpp"

namespace bakcyl {
namespace core {

Authenticator::Authenticator(bakcyl::database::Database& db) : database(db) {}

bool Authenticator::isPasswordStrong(const std::string& password) const {
  const size_t minPasswordLength = 8;
  const bool hasUpperCase =
      std::any_of(password.begin(), password.end(), ::isupper);
  const bool hasDigit =
      std::any_of(password.begin(), password.end(), ::isdigit);

  return password.length() >= minPasswordLength && hasUpperCase && hasDigit;
}

std::string Authenticator::authenticateUser(const std::string& username,
                                            const std::string& password) const {
  if (database.loginCheck(username, password)) {
    return database.getToken(username, password);
  }

  return "";
}

std::pair<int, std::string> Authenticator::registerUser(
    const std::string& username, const std::string& password,
    const std::string& email) {
  TokenGenerator tokenGen;

  if (!isPasswordStrong(password)) {
    return std::pair<int, std::string>(1, "");
  }

  if (database.createUser(username, password, email,
                          tokenGen.generateToken())) {
    return std::pair<int, std::string>(0,
                                       database.getToken(username, password));
  }

  return std::pair<int, std::string>(2, "");
}

bool Authenticator::tokenCheck(const std::string& token) const {
  return database.tokenCheck(token);
}

}  // namespace core
}  // namespace bakcyl