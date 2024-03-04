#pragma once

#include "oatpp/network/Server.hpp"

namespace bakcyl {
namespace api {

class EnvironmentWrapper {
 public:
  EnvironmentWrapper() { oatpp::base::Environment::init(); }

  ~EnvironmentWrapper() { oatpp::base::Environment::destroy(); }
};

}
}