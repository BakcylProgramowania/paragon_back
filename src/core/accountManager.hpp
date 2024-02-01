#pragma once

#include "database/database.hpp"

class AccountManager {
  Database database;

 public:
  AccountManager();
  
  bool changeBalance(const std::string& token, double amount);
  double getBalance(const std::string& token) const;
};
