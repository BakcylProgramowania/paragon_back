#pragma once

#include <boost/uuid/uuid_generators.hpp>
#include <string>

namespace bakcyl {
namespace core {

class TokenGenerator {
 public:
  std::string generateToken() const;
};

}  // namespace core
}  // namespace bakcyl