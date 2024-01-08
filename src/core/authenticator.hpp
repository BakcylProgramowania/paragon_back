#ifndef AUTHENTICATOR_HPP
#define AUTHENTICATOR_HPP

#include "database/database.hpp"
#include <string>

class Authenticator {
    Database database;
public:
    bool authenticateUser(const std::string& username, const std::string& password) const;
};

#endif