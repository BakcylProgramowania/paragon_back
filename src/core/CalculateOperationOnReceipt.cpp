#include "CalculateOperationOnReceipt.hpp"

CalculateOperationOnReceipt::CalculateOperationOnReceipt(Database& db) : database(db) {}

std::vector<User>& CalculateOperationOnReceipt::calculateReceipt(const std::vector<Item>& items) const{
    std::vector<User> users;

    for(auto item : items){
        int cost = item.price * item.amount;
        bool foundEqualUserID = false;
        for(auto user : users){
                if(user.userID == item.whoBuy){
                    user.price += cost;
                    foundEqualUserID = true;
                    break;
                }
        } 
        if (!foundEqualUserID) {
            User user = {item.whoBuy, cost};
            users.push_back(user);
        }
    }

    for(auto user : users){
        database.changeBalance(user.userID, database.getBalance(user.userID) + user.price);
    }
    return users;
};