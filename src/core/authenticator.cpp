#include "authenticator.hpp"

Authenticator::Authenticator()
    : database(
          "mongodb+srv://"
          "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/") {}

bool Authenticator::authenticateUser(const std::string& username,
                                     const std::string& password) const {
  return database.loginCheck(username, password);
}

bool Authenticator::registerUser(const std::string& username,
                                 const std::string& password,
                                 const std::string& email) {
  Token token;
  return database.createUser(username, password, email, token.createToken(username, password));
}