#include "databaseImpl.hpp"

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

namespace bakcyl {
namespace database {

DatabaseImpl::DatabaseImpl(const std::string& address)
    : uri(mongocxx::uri(address)),
      client(mongocxx::client(uri)),
      database(client["ParagonApp"]){};

// Checks if is there user with given email
bool DatabaseImpl::isThereUserWithThisEmail(const std::string& email) const {
  auto collection = database["users"];

  // searching for user with this email and returning result
  auto cursor = collection.find_one(make_document(kvp("Email", email)));
  if (cursor)
    return true;
  else
    return false;
}

// Checks if is there user with given Username
bool DatabaseImpl::isThereUserWithThisUsername(
    const std::string& username) const {
  auto collection = database["users"];

  // searching for user with this username and returning result
  auto cursor = collection.find_one(make_document(kvp("UserName", username)));
  if (cursor)
    return true;
  else
    return false;
}

bool DatabaseImpl::isUserPasswordEqualGivenPassword(
    mongocxx::cursor& cursor, const std::string& password) const {
  for (auto&& doc : cursor) {
    // Geting user's Password and saving it as a userPassword
    auto userElementPassword = doc["Password"];
    auto userPassword = userElementPassword.get_string().value;

    // if 'userPassword' == 'Password' and return result
    if (userPassword.compare(password) == 0) {
      return true;
    } else
      return false;
  }
  return false;
}

// creating new user
// returns true if user was created
// returns false if there is already user with that username or email(new user
// was not created)
bool DatabaseImpl::createUser(const std::string& username,
                              const std::string& password,
                              const std::string& email,
                              const std::string& token) {
  auto collection = database["users"];
  auto collection_userFriendList = database["userFriendList"];
  if (isThereUserWithThisUsername(username) ||
      isThereUserWithThisEmail(email)) {
    return false;
  } else {
    collection.insert_one(make_document(
        kvp("UserName", username), kvp("Password", password),
        kvp("Email", email), kvp("Token", token), kvp("Balance", 0.00)));

    collection_userFriendList.insert_one(
        make_document(kvp("UserID", getUserIDUsingToken(token)),
                      kvp("UserFriendList", make_array())));
  }
  return true;
}

// deletes user
// id can be either email or username
// needs password of this user
// returns true if user was deleted and false if user was not deleted(password
// is incorrect or there is no user with this id)
bool DatabaseImpl::deleteUser(const std::string& id,
                              const std::string& password) {
  auto collection = database["users"];

  // Checking if the 'id' is a Username or Email
  if (isThereUserWithThisUsername(id))  // id is an Username
  {
    // Finding user by Username
    auto cursor = collection.find(make_document(kvp("UserName", id)));
    if (isUserPasswordEqualGivenPassword(cursor, password)) {
      collection.delete_one(make_document(kvp("UserName", id)));
      return true;
    } else
      return false;
  } else if (isThereUserWithThisEmail(id))  // id is an Email
  {
    // Finding user by Email
    auto cursor = collection.find(make_document(kvp("Email", id)));
    if (isUserPasswordEqualGivenPassword(cursor, password)) {
      collection.delete_one(make_document(kvp("Email", id)));
      return true;
    } else
      return false;
  } else
    return false;  // there is no user with this id

  return false;
}

// Checks if there is user with given 'id' and if user's password equals given
// 'Password' returns true if 'id' and 'Password' are correct, false if not
bool DatabaseImpl::loginCheck(const std::string& id,
                              const std::string& password) const {
  // id can be either email or username
  auto collection = database["users"];

  // Checking if id is Username or Email
  if (isThereUserWithThisUsername(id)) {
    // Finding user by Username
    auto cursor = collection.find(make_document(kvp("UserName", id)));
    return isUserPasswordEqualGivenPassword(cursor, password);
  } else if (isThereUserWithThisEmail(id)) {
    // Finding user by Email
    auto cursor = collection.find(make_document(kvp("Email", id)));
    return isUserPasswordEqualGivenPassword(cursor, password);
  } else
    return false;

  return false;
}

std::string DatabaseImpl::getToken(const std::string& username,
                                   const std::string& password) {
  auto collection = database["users"];

  // Check if there is a user with the provided username
  if (isThereUserWithThisUsername(username)) {
    // Find the user by username
    auto cursor = collection.find(make_document(kvp("UserName", username)));

    // Check if the provided password matches the stored password for the user
    if (isUserPasswordEqualGivenPassword(cursor, password)) {
      // Retrieve the token from the user document
      for (auto&& doc : cursor) {
        auto tokenElement = doc["Token"];
        return tokenElement.get_string().value.to_string();
      }
    }
  }

  return "";
}

bool DatabaseImpl::tokenCheck(const std::string& token) const {
  auto collection = database["users"];

  auto cursor = collection.find_one(make_document(kvp("Token", token)));

  return cursor ? true : false;
}

bool DatabaseImpl::changeBalance(const std::string& userID, double amount) {
  auto collection = database["users"];

  bsoncxx::oid document_id(userID);

  auto doc = make_document(kvp("_id", document_id));
  auto update =
      make_document(kvp("$set", make_document(kvp("Balance", amount))));

  auto result = collection.update_one(doc.view(), update.view());

  if (result) {
    if (result.value().modified_count() > 0)
      return true;
    else
      return false;
  } else
    return false;
}

double DatabaseImpl::getBalance(const std::string& userID) const {
  auto collection = database["users"];

  bsoncxx::oid document_id(userID);

  bsoncxx::stdx::optional<bsoncxx::document::value> isUser =
      collection.find_one(make_document(kvp("_id", document_id)));

  if (isUser) {
    bsoncxx::document::value userDoc = isUser.value();
    bsoncxx::document::view userView = userDoc.view(); 

    // Pobierz saldo uÅ¼ytkownika
    auto balanceElement = userView["Balance"];
    if (balanceElement) {
      double balance = balanceElement.get_double().value;
      return balance;
    } else {
      return 0.0;  //  user doesn't have balance "balance"
    }
  } else {
    return 0.0;  // user not found
  }
}

std::vector<std::pair<std::string, std::string>>
DatabaseImpl::returnUserFriendList(const std::string& userID) const {
  auto collection_usersFriendList = database["userFriendList"];
  auto collection_users = database["users"];
  std::vector<std::pair<std::string, std::string>> friendList;

  mongocxx::v_noabi::pipeline pipeline;
  pipeline.match(make_document(kvp("UserID", userID)));
  pipeline.unwind("$UserFriendList");

  auto cursor = collection_usersFriendList.aggregate(pipeline);

  for (const auto& doc : cursor) {
    bsoncxx::document::view view = doc;

    for (const auto& element : view) {
      std::string field_name = element.key().to_string();

      if (field_name != "UserFriendLists" && field_name != "UserID") {
        if (element.type() == bsoncxx::type::k_utf8) {
          std::string idOfFriend = element.get_string().value.to_string();

          bsoncxx::oid document_id(idOfFriend);

          auto cursorOfFriends =
              collection_users.find_one(make_document(kvp("_id", document_id)));

          if (cursorOfFriends) {
            auto doc_view = cursorOfFriends->view();
            auto element = doc_view["UserName"];
            if (element) {
              std::string username = element.get_string().value.to_string();
              friendList.push_back(make_pair(idOfFriend, username));
            }
          }
        }
      }
    }
  }

  return friendList;
}

bool DatabaseImpl::addUserToFriendList(const std::string& userID,
                                       const std::string& friendUsernameToAdd) const {
  auto collection = database["userFriendList"];

  auto cursor = collection.find_one(
      make_document(kvp("UserID", userID),
                    kvp("UserFriendList",
                        make_document(kvp("$in", make_array(getUserIDUsingUsername(friendUsernameToAdd)))))));
  if (cursor) return false;

  cursor = collection.find_one(make_document(kvp("UserID", userID)));
  if (cursor) {
    auto result = collection.update_one(
        make_document(kvp("UserID", userID)),
        make_document(kvp(
            "$addToSet", make_document(kvp("UserFriendList", getUserIDUsingUsername(friendUsernameToAdd))))));
    if (result) return true;
  }

  return false;
}

bool DatabaseImpl::removeUserFromFriendList(
    const std::string& userID, const std::string& friendUsernameToRemove) const {
  auto collection = database["userFriendList"];

  auto cursor = collection.find_one(make_document(
      kvp("UserID", userID),
      kvp("UserFriendList",
          make_document(kvp("$in", make_array(getUserIDUsingUsername(friendUsernameToRemove)))))));
  if (!cursor) return false;

  cursor = collection.find_one(make_document(kvp("UserID", userID)));
  if (cursor) {
    auto result = collection.update_one(
        make_document(kvp("UserID", userID)),
        make_document(kvp(
            "$pull", make_document(kvp("UserFriendList", getUserIDUsingUsername(friendUsernameToRemove))))));
    if (result) return true;
  }

  return false;
}

// returns UserID of User with given token. returns "" if there is no user with
// this token
std::string DatabaseImpl::getUserIDUsingToken(const std::string& token) const {
  auto collection = database["users"];

  auto cursor = collection.find(make_document(kvp("Token", token)));
  for (auto&& doc : cursor) {
    auto idElement = doc["_id"];
    return idElement.get_oid().value.to_string();
  }

  return "";
}

bool DatabaseImpl::isThereUserWithThisID(const std::string& userID) const {
  auto collection = database["users"];
  
  try {
    bsoncxx::oid oid(userID);
    auto cursor = collection.find_one(make_document(kvp("_id", oid)));
    
    if (cursor)
      return true;
    else
      return false;
  } catch(const std::exception& e) {
    return false;
  }
}

int DatabaseImpl::createReceiptInHistory(const bakcyl::core::Receipt& receipt) {
  auto collection = database["receiptHistory"];
  auto usersIncluded = bsoncxx::builder::basic::array{};
  auto items = bsoncxx::builder::basic::array{};
  auto mergedReceipts = bsoncxx::builder::basic::array{};

  for(const auto& element : receipt.usersIncluded)
  {
    usersIncluded.append(element);
  }

  for(const auto& element : receipt.items)
  {
    items.append(make_document(kvp("whoBuy", element.whoBuy), kvp("itemName", element.itemName), kvp("price", element.price)));
  }

  if(receipt.mergedReceipts.size() > 0)
  {
    for(const auto& element : receipt.mergedReceipts)
    {
      mergedReceipts.append(element);
    }
    collection.insert_one(make_document(
      kvp("author", receipt.author),
      kvp("receiptName", receipt.receiptName),
      kvp("date", receipt.date),
      kvp("usersIncluded", usersIncluded),
      kvp("items", items),
      kvp("merged", false),
      kvp("mergedReceipts", mergedReceipts)
    ));
  }
  else
  {
    collection.insert_one(make_document(
      kvp("author", receipt.author),
      kvp("receiptName", receipt.receiptName),
      kvp("date", receipt.date),
      kvp("usersIncluded", usersIncluded),
      kvp("items", items),
      kvp("merged", false)
    ));
  }

  return 0;
}

bakcyl::core::Receipt DatabaseImpl::getReceipt(const std::string& receiptID) {
  
  auto collection = database["receiptHistory"];
  bakcyl::core::Receipt receipt;

  bsoncxx::oid document_id(receiptID);
  auto cursor = collection.find_one(make_document(kvp("_id", document_id)));

  auto doc_view = cursor->view();

  receipt.author = doc_view["author"].get_string().value.to_string();
  receipt.date = doc_view["date"].get_string().value.to_string();
  receipt.receiptName = doc_view["receiptName"].get_string().value.to_string();

  auto array_value_usersIncluded = doc_view["usersIncluded"];
  if (array_value_usersIncluded && array_value_usersIncluded.type() == bsoncxx::type::k_array) {
            
    for (const auto& element : array_value_usersIncluded.get_array().value) {
      receipt.usersIncluded.push_back(element.get_string().value.to_string());
    }
  }
  
  auto array_value_mergedReceipts = doc_view["mergedReceipts"];
  if (array_value_mergedReceipts && array_value_mergedReceipts.type() == bsoncxx::type::k_array) {
            
    for (const auto& element : array_value_mergedReceipts.get_array().value) {
      receipt.mergedReceipts.push_back(element.get_string().value.to_string());
    }
  }

  auto array_value_items = doc_view["items"];
  
  if (array_value_items && array_value_items.type() == bsoncxx::type::k_array) {
    for (auto& object : array_value_items.get_array().value) {
      bakcyl::core::Item item;

      item.itemName = object["itemName"].get_string().value.to_string();

      if(object["price"].type() == bsoncxx::type::k_double) {
        item.price = object["price"].get_double().value;  
      }
      else
      {
        item.price = object["price"].get_int32().value;
      }

      item.whoBuy = object["whoBuy"].get_string().value.to_string();

      receipt.items.push_back(item); 
    }
  }

  return receipt;
}

bool bakcyl::database::DatabaseImpl::changeIfMerged(const std::string& receiptID, const bool& newState) {
  auto collection = database["receiptHistory"];

  bsoncxx::oid document_id(receiptID);
  auto cursor = collection.find_one(make_document(kvp("_id", document_id)));
  auto doc_view = cursor->view();
  if(doc_view["merged"].get_bool().value == newState)
  {
    return false;
  }

  collection.update_one(make_document(kvp("_id", document_id)) ,make_document(kvp("$set", make_document(kvp("merged", newState)))));

  return true;
}

std::vector<bakcyl::core::ReceiptShortView> bakcyl::database::DatabaseImpl::getReceipts(const std::string& authorID) {
  auto collection = database["receiptHistory"];

  std::vector<bakcyl::core::ReceiptShortView> receipts;

  auto cursor = collection.find(make_document(kvp("author", authorID), kvp("merged", false)));
  for(auto doc : cursor)
  {
    bakcyl::core::ReceiptShortView receipt;

    receipt.receiptName = doc["receiptName"].get_string().value.to_string();
    receipt.receiptID = doc["_id"].get_oid().value.to_string();
    receipts.push_back(receipt);
  }
  return receipts;
}

std::string bakcyl::database::DatabaseImpl::getUserIDUsingUsername(const std::string& username) const {
  auto collection = database["users"];

  auto cursor = collection.find(make_document(kvp("UserName", username)));

  for (auto&& doc : cursor) {
    auto idElement = doc["_id"];
    return idElement.get_oid().value.to_string();
  }

  return "";
}

}
}
