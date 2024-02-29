#include <vector>

#include "database/database.hpp"
#include "structures.hpp"

class ReciptOperations {
  Database& database;

 public:
  ReciptOperations(Database& db);

  std::vector<User> calculateReceipt(const std::vector<Item>& items) const;
};
