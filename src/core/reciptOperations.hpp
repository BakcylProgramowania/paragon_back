#include <vector>
#include "structures.hpp"
#include "database/database.hpp"

class ReciptOperations {
    Database& database;

    public:
    ReciptOperations(Database& db);

    std::vector<User>& calculateReceipt(const std::vector<Item>& items) const;
};
