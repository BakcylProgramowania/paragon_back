#pragma once

#include "database/database.hpp"
#include <string>

class Authenticator {
    Database database;
public:
    Authenticator();
    bool authenticateUser(const std::string& username, const std::string& password) const;
};