#include <ctime>
#include <vector>

#include "database/database.hpp"
#include "structures.hpp"

namespace bakcyl {
namespace core {

class ReceiptOperations {
  bakcyl::database::Database& database;
  
 public:
  ReceiptOperations(bakcyl::database::Database& db);

  std::vector<bakcyl::core::User> calculateReceipt(
      const std::vector<bakcyl::core::Item>& items) const;
  int mergeReceipt(std::vector<std::string>& receiptIDs,
                   std::string& receiptName,
                   std::string& author)  const;
  int saveReceipt(bakcyl::core::Receipt& receipt) const;
};

}  // namespace core
}  // namespace bakcyl
