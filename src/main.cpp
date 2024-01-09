#include <iostream>

#include "api/Api.cpp"
#include "api/EnvironmentWrapper.hpp"
#include "core/core.cpp"
#include "database/database.hpp"
#include "example/Example.hpp"

int main(int argc, const char* argv[]) {
  EnvironmentWrapper environmentWrapper;

  run();

  return 0;
}
