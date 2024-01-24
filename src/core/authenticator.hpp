#pragma once

#include <iostream>
#include <string>

#include "database/database.hpp"
#include "core/token.hpp"

class Authenticator {
  Database database;

 public:
  Authenticator();
  bool authenticateUser(const std::string& username,
                        const std::string& password) const;

  std::string registerUser(const std::string& username, const std::string& password,
                    const std::string& email);
};