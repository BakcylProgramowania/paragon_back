#include <vector>
#include "structures.hpp"
#include "database/database.hpp"

class CalculateOperationOnReceipt{
    Database& database;

    public:
    CalculateOperationOnReceipt(Database& db);

    std::vector<User>& calculateReceipt(const std::vector<Item>& items) const;
};
