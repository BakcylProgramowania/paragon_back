#include <iostream>

#include "api/Api.cpp"
#include "api/EnvironmentWrapper.hpp"
#include "core/core.cpp"
#include "database/database.hpp"
#include "example/Example.hpp"

int main(int argc, const char* argv[]) {
  EnvironmentWrapper environmentWrapper;

  Database database("mongodb+srv://bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/");
  database.changeBalance("6580b94031f3363eddb52347", 2137);
  //run();

  return 0;
}
