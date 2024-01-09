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

    bool isThereUserWithThisUsername(const std::string& Username) const;
    bool isThereUserWithThisEmail(const std::string& Email) const;
    bool isUserPasswordEqualGivenPassword(mongocxx::cursor& cursor, const std::string& Password) const;
    bool createUser(const std::string& Username, const std::string& Password, const std::string& Email);
    bool deleteUser(const std::string& id, const std::string& Password);
    bool loginCheck(const std::string& id, const std::string& Password) const;

};