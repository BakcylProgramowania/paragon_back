#include "accountManager.hpp"

AccountManager::AccountManager(Database& db) : database(db) {} // Update constructor

          
bool AccountManager::changeBalance(const std::string& token, double amount) {
    return database.changeBalance(token, amount);
}

double AccountManager::getBalance(const std::string& token) const{
    return database.getBalance(token);
}

std::vector<std::pair<std::string, std::string>> AccountManager::returnUserFriendList(const std::string& token) const {
    return database.returnUserFriendList(database.getUserIDUsingToken(token));
}