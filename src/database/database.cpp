#include "database.hpp"

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

class DatabaseImpl {
  private:
  mongocxx::uri uri;
  mongocxx::client client;
  mongocxx::database database;
  bool isUserPasswordEqualGivenPassword(mongocxx::cursor& cursor,
                                        const std::string& password) const;
 public:
  DatabaseImpl(const std::string& address);
  ~DatabaseImpl() = default;

  bool isThereUserWithThisUsername(const std::string& username) const;
  bool isThereUserWithThisEmail(const std::string& email) const;
  bool createUser(const std::string& username, const std::string& password,
                  const std::string& email);
  bool deleteUser(const std::string& id, const std::string& password);
  bool loginCheck(const std::string& id, const std::string& password) const;
};

DatabaseImpl::DatabaseImpl(const std::string& address)
    : uri(mongocxx::uri(address)),
      client(mongocxx::client(uri)),
      database(client["ParagonApp"]) {}

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
bool DatabaseImpl::isThereUserWithThisUsername(const std::string& username) const {
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
                          const std::string& email) {
  auto collection = database["users"];
  if (isThereUserWithThisUsername(username) ||
      isThereUserWithThisEmail(email)) {
    return false;
  } else {
    auto resultOfInsert = collection.insert_one(
        make_document(kvp("UserName", username), kvp("Password", password),
                      kvp("Email", email)));
  }
  return true;
}

// deletes user
// id can be either email or username
// needs password of this user
// returns true if user was deleted and false if user was not deleted(password
// is incorrect or there is no user with this id)
bool DatabaseImpl::deleteUser(const std::string& id, const std::string& password) {
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

  Database::Database(const std::string& address) : impl(new DatabaseImpl(address)) {};
  Database::~Database() = default;
  
  bool Database::isThereUserWithThisUsername(const std::string& username) const
  {
    return impl->isThereUserWithThisUsername(username);
  }

  bool Database::isThereUserWithThisEmail(const std::string& email) const
  {
    return impl->isThereUserWithThisEmail(email);
  }

  bool Database::createUser(const std::string& username, const std::string& password,
                  const std::string& email)
  {
    return impl->createUser(username, password, email);
  }

  bool Database::deleteUser(const std::string& id, const std::string& password)
  {
      return impl->deleteUser(id, password);
  }

  bool Database::loginCheck(const std::string& id, const std::string& password) const
  {
    return impl->loginCheck(id, password);
  }