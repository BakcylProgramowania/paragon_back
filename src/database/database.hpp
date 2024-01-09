#pragma once

#include <iostream>
#include <cstdint>
#include <vector>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

class Database
{
    private:
    mongocxx::uri uri;
    mongocxx::client client;
    mongocxx::database database;

    public:
    Database(const std::string& address);
    ~Database()=default;

    bool isThereUserWithThisUsername(const std::string& username) const;
    bool isThereUserWithThisEmail(const std::string& email) const;
    bool isUserPasswordEqualGivenPassword(mongocxx::cursor& cursor, const std::string& password) const;
    bool createUser(const std::string& username, const std::string& password, const std::string& email);
    bool deleteUser(const std::string& id, const std::string& password);
    bool loginCheck(const std::string& id, const std::string& password) const;

};