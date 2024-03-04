#include <vector>

#include "database/database.hpp"
#include "structures.hpp"

namespace bakcyl {
namespace core {

class ReciptOperations {
  bakcyl::database::Database& database;

 public:
  ReciptOperations(bakcyl::database::Database& db);

  std::vector<bakcyl::core::User> calculateReceipt(const std::vector<bakcyl::core::Item>& items) const;
};

}
}