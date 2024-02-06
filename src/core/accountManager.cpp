#include "accountManager.hpp"

AccountManager::AccountManager(Database& db) : database(db) {} // Update constructor

          
bool AccountManager::changeBalance(const std::string& token, double amount) {
    return database.changeBalance(token, amount);
}

double AccountManager::getBalance(const std::string& token) const{
    return database.getBalance(token);
}