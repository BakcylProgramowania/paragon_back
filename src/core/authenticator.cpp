#include "authenticator.hpp"

namespace bakcyl {
namespace core {

Authenticator::Authenticator()
    : database(
          "mongodb+srv://"
          "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/") {}

bool Authenticator::authenticateUser(const std::string& username,
                                     const std::string& password) const {
  return database.loginCheck(username, password);
}

}
}