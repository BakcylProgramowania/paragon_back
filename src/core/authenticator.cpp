#include "authenticator.hpp"

Authenticator::Authenticator()
    : database(
          "mongodb+srv://"
          "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/") {}

bool Authenticator::authenticateUser(const std::string& username,
                                     const std::string& password) const {
  return database.loginCheck(username, password);
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