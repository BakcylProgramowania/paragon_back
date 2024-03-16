#include "receiptOperations.hpp"

namespace bakcyl {
namespace core {

ReceiptOperations::ReceiptOperations(bakcyl::database::Database& db)
    : database(db) {}

std::vector<bakcyl::core::User> ReceiptOperations::calculateReceipt(
    const std::vector<bakcyl::core::Item>& items) const {
  std::vector<bakcyl::core::User> users;

  for (const auto& item : items) {
    int cost = item.price * item.amount;
    bool foundEqualUserID = false;

    if (!database.isThereUserWithThisID(item.whoBuy)) return {};
    
    for (auto& user : users) {
      if (user.userID == item.whoBuy) {
        user.price += cost;
        foundEqualUserID = true;
        break;
      }
    }

    if (!foundEqualUserID) {
      bakcyl::core::User user = {item.whoBuy, cost};
      users.push_back(user);
    }
  }

  for (const auto& user : users) {
    database.changeBalance(user.userID,
                           database.getBalance(user.userID) + user.price);
  }

  return users;
};

int ReceiptOperations::mergeReceipt(std::vector<std::string>& receiptIDs, std::string& receiptName, std::string& author) const{
  bakcyl::core::Receipt mergedReceipt;
  std::vector<bakcyl::core::Item> items;
  
  if (!database.isThereUserWithThisID(author)) return {};

  mergedReceipt.receiptName = receiptName;
  mergedReceipt.author = author;
  mergedReceipt.mergedReceipts = receiptIDs;
  
  for (auto& receiptId : receiptIDs) {
    bakcyl::core::Receipt receipt = database.getReceipt(receiptId);
    items.insert(items.end(), receipt.items.begin(), receipt.items.end());
    
    database.changeIfMerged(receiptId, true);
  }

  return saveReceipt(mergedReceipt);
};

int ReceiptOperations::unmergeReceipt(std::string& mergedReceiptID) const{
  bakcyl::core::Receipt receipt = database.getReceipt(mergedReceiptID);
  std::vector<bakcyl::core::ReceiptShortView> receiptsShortView = database.getReceipts(receipt.author);
  
  for (auto& receiptID : receipt.mergedReceipts) {
    for (auto& receiptShortView : receiptsShortView) {
      if (receiptID == receiptShortView.receiptID) {
        database.changeIfMerged(receiptID, false);
        break;
      }
    }
  }

  return database.changeIfMerged(mergedReceiptID, true);
};

int ReceiptOperations::saveReceipt(bakcyl::core::Receipt& receipt) const {
  std::vector<std::string> usersIncluded;
  
  receipt.date = std::to_string(time(0));
  for (auto& item : receipt.items) {
    item.price = item.price * item.amount;
    item.amount = 0;

    bool found = false;
    for(const auto& user : usersIncluded) {
      if(user == item.whoBuy) {
        found = true;
        break;
      }
    }
    if(!found)
      usersIncluded.push_back(item.whoBuy);
  }
  receipt.usersIncluded = usersIncluded;
  return database.createReceiptInHistory(receipt);
};

}  // namespace core
}  // namespace bakcyl