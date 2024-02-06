#pragma once

#include <string>

#include "core/token.hpp"
#include "database/database.hpp"

class Authenticator {
  Database& database;
  bool isPasswordStrong(const std::string& password) const;

public:
  Authenticator(Database& db);

  std::string authenticateUser(const std::string& username,
                               const std::string& password) const;

  std::pair<int, std::string> registerUser(const std::string& username,
                                           const std::string& password,
                                           const std::string& email);
  bool tokenCheck(const std::string& token) const;
};