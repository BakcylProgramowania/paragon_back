#include <iostream>

#include "api/Api.cpp"
#include "api/EnvironmentWrapper.hpp"
#include "core/core.cpp"
#include "example/Example.hpp"
#include "database/database.hpp"

int main(int argc, const char* argv[]) {
  EnvironmentWrapper environmentWrapper;

  run();

  return 0;
}
