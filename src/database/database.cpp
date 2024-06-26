#include "database.hpp"

#include "databaseImpl.hpp"

namespace bakcyl {
namespace database {

Database::Database(const std::string& address)
    : impl(new DatabaseImpl(address)){};
Database::~Database() = default;

bool bakcyl::database::Database::createUser(const std::string& username,
                                            const std::string& password,
                                            const std::string& email,
                                            const std::string& token) {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->createUser(username, password, email,
                                                      token);
}

bool bakcyl::database::Database::deleteUser(const std::string& id,
                                            const std::string& password) {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->deleteUser(id, password);
}

bool bakcyl::database::Database::loginCheck(const std::string& id,
                                            const std::string& password) const {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->loginCheck(id, password);
}

std::string bakcyl::database::Database::getToken(
    const std::string& username, const std::string& password) const {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->getToken(username, password);
}

bool bakcyl::database::Database::tokenCheck(const std::string& token) const {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->tokenCheck(token);
}

bool bakcyl::database::Database::changeBalance(const std::string& userID,
                                               double amount) {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->changeBalance(userID, amount);
}

double bakcyl::database::Database::getBalance(const std::string& userID) const {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->getBalance(userID);
}

std::vector<std::pair<std::string, std::string>>
bakcyl::database::Database::returnUserFriendList(
    const std::string& userID) const {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->returnUserFriendList(userID);
}

bool bakcyl::database::Database::addUserToFriendList(
    const std::string& userID, const std::string& friendUsernameToAdd) const {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->addUserToFriendList(
      userID, friendUsernameToAdd);
}

bool bakcyl::database::Database::removeUserFromFriendList(
    const std::string& userID,
    const std::string& friendUsernameToRemove) const {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->removeUserFromFriendList(
      userID, friendUsernameToRemove);
}

std::string bakcyl::database::Database::getUserIDUsingToken(
    const std::string& token) const {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->getUserIDUsingToken(token);
}

bool bakcyl::database::Database::isThereUserWithThisID(
    const std::string& userID) const {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->isThereUserWithThisID(userID);
}

int bakcyl::database::Database::createReceiptInHistory(
    const bakcyl::core::Receipt& receipt) {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->createReceiptInHistory(receipt);
}

bakcyl::core::Receipt bakcyl::database::Database::getReceipt(
    const std::string& receiptID) {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->getReceipt(receiptID);
}

bool bakcyl::database::Database::changeIfMerged(const std::string& receiptID,
                                                const bool& newState) {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->changeIfMerged(receiptID, newState);
}

std::vector<bakcyl::core::ReceiptShortView>
bakcyl::database::Database::getReceipts(const std::string& userID) {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->getReceipts(userID);
}

bool bakcyl::database::Database::paidForItem(const std::string& receiptID,
                                             const std::string& itemName,
                                             const std::string& whoBuy) {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->paidForItem(receiptID, itemName,
                                                       whoBuy);
}

std::vector<bakcyl::core::ItemToPay> bakcyl::database::Database::getItemsToPay(
    const std::string& userID) {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->getItemsToPay(userID);
}

std::string bakcyl::database::Database::getUserIDUsingUsername(
    const std::string& username) const {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->getUserIDUsingUsername(username);
}

bool bakcyl::database::Database::isThereUserWithThisUsername(
    const std::string& username) const {
  std::lock_guard<std::mutex> lock(mtx);
  return bakcyl::database::Database::impl->isThereUserWithThisUsername(
      username);
}

}  // namespace database
}  // namespace bakcyl