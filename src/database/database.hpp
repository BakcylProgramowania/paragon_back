#pragma once

#include <memory>
#include <string>

class DatabaseImpl;

class Database {
 public:
  Database(const std::string& address);
  ~Database();

  bool createUser(const std::string& username, const std::string& password,
                  const std::string& email, const std::string& token);
  bool deleteUser(const std::string& id, const std::string& password);
  bool loginCheck(const std::string& id, const std::string& password) const;
  std::string getToken(const std::string& username,
                       const std::string& password) const;
  bool tokenCheck(const std::string& token) const;
  bool changeBalance(const std::string& token, double amount);
  double getBalance(const std::string& token) const;

 private:
  std::unique_ptr<DatabaseImpl> impl;
};