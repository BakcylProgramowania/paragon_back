#include "receiptOperations.hpp"

namespace bakcyl {
namespace core {

ReceiptOperations::ReceiptOperations(bakcyl::database::Database& db)
    : database(db) {}

std::vector<bakcyl::core::User> ReceiptOperations::calculateReceipt(
    const std::vector<bakcyl::core::Item>& items) const {
  std::vector<bakcyl::core::User> users;

  for (const auto& item : items) {

    float cost = item.price * item.amount;

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
  
  if (!database.isThereUserWithThisID(author)) return {};

  mergedReceipt.mergedReceipts = receiptIDs;
  mergedReceipt.receiptName = receiptName;
  mergedReceipt.author = author;
  
  for (auto& receiptId : receiptIDs) {
    bakcyl::core::Receipt receipt = database.getReceipt(receiptId);

    for (bakcyl::core::Item& Receipt : receipt.items) {
      Receipt.amount = 1;
      mergedReceipt.items.push_back(Receipt);
    } // lepsza nazwa dla Receipt

    database.changeIfMerged(receiptId, true);
  }

  return saveReceipt(mergedReceipt);
};

int ReceiptOperations::unmergeReceipt(std::string& mergedReceiptID) const {
  bakcyl::core::Receipt receipt = database.getReceipt(mergedReceiptID);

  for (auto& receiptID : receipt.mergedReceipts)
    database.changeIfMerged(receiptID, false);

  database.changeIfMerged(mergedReceiptID, true);

  return 0;
};

int ReceiptOperations::saveReceipt(bakcyl::core::Receipt& receipt) const {
  std::vector<std::string> usersIncluded;

  receipt.date = std::to_string(time(0));

  for (auto& item : receipt.items) {
    item.price = item.price * item.amount;
    item.amount = 0;

    bool found = false;

    for (const auto& user : usersIncluded) {
      if (user == item.whoBuy) {
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

std::vector<bakcyl::core::ReceiptShortView> ReceiptOperations::getReceipts(
    const std::string& token) const {
  return database.getReceipts(database.getUserIDUsingToken(token));
};

bakcyl::core::Receipt ReceiptOperations::getReceipt(
    const std::string& receiptID) {
  return database.getReceipt(receiptID);
};

bool ReceiptOperations::paidForItem(const std::string& receiptID,
                                    const std::string& itemName,
                                    const std::string& token) const {
  return database.paidForItem(receiptID, itemName,
                              database.getUserIDUsingToken(token));
};

std::vector<bakcyl::core::ItemToPay> ReceiptOperations::getItemsToPay(
    const std::string& token) const {
  return database.getItemsToPay(database.getUserIDUsingToken(token));
};

}  // namespace core
}  // namespace bakcyl