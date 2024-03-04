#include <string>

namespace bakcyl {
namespace core {

struct User {
  std::string userID;
  int price;
};

struct Item {
  std::string whoBuy;
  std::string itemName;
  int price;
  int amount;
};

}
}