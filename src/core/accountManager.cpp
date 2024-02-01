#include "accountManager.hpp"

AccountManager::AccountManager()
    : database(
          "mongodb+srv://"
          "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/") {}
          
bool AccountManager::changeBalance(const std::string& token, double amount) {
    return database.changeBalance(token, amount);
}

double AccountManager::getBalance(const std::string& token) const{
    return database.getBalance(token);
}