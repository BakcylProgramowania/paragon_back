#pragma once

#include "database/database.hpp"

class AccountManager {
  Database& database; // Change to reference

public:
  AccountManager(Database& db); // Modify constructor
  
  bool changeBalance(const std::string& token, double amount);
  double getBalance(const std::string& token) const;
};
