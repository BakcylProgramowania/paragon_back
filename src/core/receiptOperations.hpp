#include <cmath>
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
                   const std::string& receiptName,
                   const std::string& author) const;
  int unmergeReceipt(std::string& mergedReceiptID) const;
  int saveReceipt(bakcyl::core::Receipt& receipt) const;
  std::vector<bakcyl::core::ReceiptShortView> getReceipts(
      const std::string& token) const;
  bakcyl::core::Receipt getReceipt(const std::string& receiptID);
  bool paidForItem(const std::string& receiptID, const std::string& itemName,
                   const std::string& token) const;
  std::vector<bakcyl::core::ItemToPay> getItemsToPay(
      const std::string& token) const;
};

}  // namespace core
}  // namespace bakcyl
