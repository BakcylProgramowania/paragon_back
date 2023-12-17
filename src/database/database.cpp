#include <iostream>

#include <cstdint>
#include <iostream>
#include <vector>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

int main()
{
  std::cout << "test";
  mongocxx::instance instance{};
  
  return 0;
}
