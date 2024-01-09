#pragma once

#include "database/database.hpp"
#include <string>

class Authenticator {
    Database database;
public:
    bool authenticateUser(const std::string& username, const std::string& password) const;
};