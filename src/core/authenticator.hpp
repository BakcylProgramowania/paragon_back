#pragma once

#include <iostream>
#include <string>

#include "database/database.hpp"
#include "core/token.hpp"

class Authenticator {
 public:
  Database database;
  Authenticator();
  std::string authenticateUser(const std::string& username,
                        const std::string& password) const;

  std::string registerUser(const std::string& username, const std::string& password,
                    const std::string& email);

  bool tokenCheck(const std::string& token) const;
};