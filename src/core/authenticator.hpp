#pragma once

#include <string>

#include "database/database.hpp"

namespace bakcyl {
namespace core {

class Authenticator {
  bakcyl::database::Database database;

 public:
  Authenticator();
  bool authenticateUser(const std::string& username,
                        const std::string& password) const;
};

}  // namespace core
}  // namespace bakcyl