#pragma once

#include <string>

#include "core/token.hpp"
#include "database/database.hpp"

class Authenticator {
  Database database;

 public:
  Authenticator();
  std::string authenticateUser(const std::string& username,
                               const std::string& password) const;

  std::string registerUser(const std::string& username,
                           const std::string& password,
                           const std::string& email);

  bool tokenCheck(const std::string& token) const;
};