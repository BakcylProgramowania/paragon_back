#include "authenticator.hpp"

bool Authenticator::authenticateUser(const std::string& username, const std::string& password) const {
    return database.loginCheck(username, password);
}