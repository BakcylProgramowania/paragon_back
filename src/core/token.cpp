#include "token.hpp"

#include <boost/uuid/uuid_io.hpp>

namespace bakcyl {
namespace core {

std::string TokenGenerator::generateToken() const {
  boost::uuids::random_generator generator;
  boost::uuids::uuid uuid = generator();

  return boost::uuids::to_string(uuid);
}

}  // namespace core
}  // namespace bakcyl