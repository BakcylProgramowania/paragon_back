#include "authenticator.hpp"

Authenticator::Authenticator()
    : database(
          "mongodb+srv://"
          "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/") {}

std::string Authenticator::authenticateUser(const std::string& username,
                                     const std::string& password) const {
  if (database.loginCheck(username, password)) {
    return database.getToken(username, password);
  }
  return "";
}

std::string Authenticator::registerUser(const std::string& username,
                                 const std::string& password,
                                 const std::string& email) {
  Token token;
  if (database.createUser(username, password, email, token.createToken(username, password)))
  {
    return database.getToken(username, password);
  }
  return "";
}

bool Authenticator::tokenCheck(const std::string& token) const {
    return database.tokenCheck(token);
}