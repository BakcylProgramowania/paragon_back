#pragma once

#include <boost/uuid/uuid_generators.hpp>
#include <string>

class TokenGenerator {
 public:
  std::string generateToken() const;
};