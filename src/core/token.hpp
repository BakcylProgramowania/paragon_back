#pragma once

#include <boost/uuid/uuid_generators.hpp>
#include <string>

class Token {
 public:
  std::string createToken(const std::string& username,
                          const std::string& email);
};
