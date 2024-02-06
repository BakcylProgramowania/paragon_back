//#include <bsoncxx/builder/basic/document.hpp>
//#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
//#include <mongocxx/instance.hpp>
//#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

class DatabaseImpl {
 public:
  DatabaseImpl(const std::string& address);
  ~DatabaseImpl() = default;
  bool createUser(const std::string& username, const std::string& password,
                  const std::string& email, const std::string& token);
  bool deleteUser(const std::string& id, const std::string& password);
  bool loginCheck(const std::string& id, const std::string& password) const;
  std::string getToken(const std::string& username,
                       const std::string& password);
  bool tokenCheck(const std::string& token) const;
  bool changeBalance(const std::string& token, double amount);
  double getBalance(const std::string& token) const;

 private:
  bool isUserPasswordEqualGivenPassword(mongocxx::cursor& cursor,
                                        const std::string& password) const;
  bool isThereUserWithThisUsername(const std::string& username) const;
  bool isThereUserWithThisEmail(const std::string& email) const;

  mongocxx::uri uri;
  mongocxx::client client;
  mongocxx::database database;
};