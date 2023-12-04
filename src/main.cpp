#include "example/Example.hpp"
#include <iostream>

int main() {
    using paragon::Example;

    Example example{13};
    std::cout << "Hello " << example.get() << std::endl;
    return 0;
}
