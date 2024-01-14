#pragma once

#include <string>
#include <memory>

class DatabaseImpl;

class Database {
 public:
  Database(const std::string& address);
  ~Database();

  bool isThereUserWithThisUsername(const std::string& username) const;
  bool isThereUserWithThisEmail(const std::string& email) const;
  bool createUser(const std::string& username, const std::string& password,
                  const std::string& email);
  bool deleteUser(const std::string& id, const std::string& password);
  bool loginCheck(const std::string& id, const std::string& password) const;

  private:
  std::unique_ptr<DatabaseImpl> impl;
};

