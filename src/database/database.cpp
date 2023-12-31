#include "database.hpp"

Database::Database()
 : uri(mongocxx::uri("mongodb+srv://bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/")),
 client(mongocxx::client(uri)),
 database(client["ParagonApp"]) {}

//Checks if is there user with given Email
bool Database::isThereUserWithThisEmail (const std::string& Email) const
{
    auto collection = database["users"];

    //searching for user with this email and returning result
    auto cursor = collection.find_one(make_document(kvp("Email", Email)));
    if(cursor) return true;
    else return false;
}

//Checks if is there user with given Username
bool Database::isThereUserWithThisUsername (const std::string& Username) const
{
    auto collection = database["users"];

    //searching for user with this username and returning result
    auto cursor = collection.find_one(make_document(kvp("UserName", Username)));
    if(cursor) return true;
    else return false;
}

bool Database::isUserPasswordEqualGivenPassword(mongocxx::cursor& cursor, const std::string& Password) const
{
    for(auto&& doc : cursor)
    {
        //Geting user's Password and saving it as a userPassword
        auto userElementPassword = doc["Password"];
        auto userPassword = userElementPassword.get_string().value;
        
        //if 'userPassword' == 'Password' and return result
        if(userPassword.compare(Password) == 0)
        {
            return true;
        }
        else return false;
    }
    return false;
}

//creating new user
//returns true if user was created
//returns false if there is already user with that username or email(new user was not created)
bool Database::createUser(const std::string& Username, const std::string& Password, const std::string& Email) 
{
    auto collection = database["users"];
    if(isThereUserWithThisUsername(Username) || isThereUserWithThisEmail(Email))
    {
        return false;
    }
    else
    {
        auto resultOfInsert = collection.insert_one(make_document(
        kvp("UserName", Username),
        kvp("Password", Password),
        kvp("Email", Email)
        ));
    }
    return true;
}

//deletes user
//id can be either email or username
//needs password of this user
//returns true if user was deleted and false if user was not deleted(password is incorrect or there is no user with this id)
bool Database::deleteUser(const std::string& id, const std::string& Password)
{
    auto collection = database["users"];

    //Checking if the 'id' is a Username or Email
    if(isThereUserWithThisUsername(id))//id is an Username
    {
        //Finding user by Username 
        auto cursor = collection.find(make_document(kvp("UserName", id)));
        if(isUserPasswordEqualGivenPassword(cursor, Password))
        {
           collection.delete_one(make_document(kvp("UserName", id)));
           return true;
        }
        else return false;
    }
    else if(isThereUserWithThisEmail(id))//id is an Email
    {
        //Finding user by Email
        auto cursor = collection.find(make_document(kvp("Email", id)));
        if(isUserPasswordEqualGivenPassword(cursor, Password))
        {
           collection.delete_one(make_document(kvp("Email", id)));
           return true;
        }
        else return false;
    }
    else return false; //there is no user with this id

    return false;
}

//Checks if there is user with given 'id' and if user's password equals given 'Password'
//returns true if 'id' and 'Password' are correct, false if not
bool Database::loginCheck(const std::string& id, const std::string& Password)
{
    //id can be either email or username
    auto collection = database["users"];

    //Checking if id is Username or Email
    if(isThereUserWithThisUsername(id))
    {
        //Finding user by Username
        auto cursor = collection.find(make_document(kvp("UserName", id)));
        return isUserPasswordEqualGivenPassword(cursor, Password);
    }
    else if(isThereUserWithThisEmail(id))
    {
        //Finding user by Email
        auto cursor = collection.find(make_document(kvp("Email", id)));
        return isUserPasswordEqualGivenPassword(cursor, Password);
    }
    else return false;

    return false;
}