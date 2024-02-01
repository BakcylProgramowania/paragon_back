#include "databaseImpl.hpp"

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

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
  if (isThereUserWithThisUsername(username) ||
      isThereUserWithThisEmail(email)) {
    return false;
  } else {
    auto resultOfInsert = collection.insert_one(make_document(
        kvp("UserName", username), kvp("Password", password),
        kvp("Email", email), kvp("Token", token), kvp("Balance", 0.00)));
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

bool DatabaseImpl::changeBalance(const std::string& token, double amount) {
  auto collection = database["users"];

  auto filter = make_document(kvp("Token", token));
  auto update =
      make_document(kvp("$set", make_document(kvp("Balance", amount))));

  auto result = collection.update_one(filter.view(), update.view());

  if (result) {
    if (result.value().modified_count() > 0)
      return true;
    else
      return false;
  } else
    return false;
}

double DatabaseImpl::getBalance(const std::string& token) const {
  auto collection = database["users"];

  bsoncxx::stdx::optional<bsoncxx::document::value> isUser =
      collection.find_one(make_document(kvp("Token", token)));

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