#include <iostream>

#include "api/Api.cpp"
#include "api/EnvironmentWrapper.hpp"

int main(int argc, const char* argv[]) {
  bakcyl::api::EnvironmentWrapper environmentWrapper;

  bakcyl::api::run();

  return 0;
}
