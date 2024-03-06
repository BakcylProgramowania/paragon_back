#include <vector>

#include "database/database.hpp"
#include "structures.hpp"

namespace bakcyl {
namespace core {

class ReceiptOperations {
  bakcyl::database::Database& database;

 public:
  ReceiptOperations(bakcyl::database::Database& db);

  std::vector<bakcyl::core::User> calculateReceipt(const std::vector<bakcyl::core::Item>& items) const;
};

}
}