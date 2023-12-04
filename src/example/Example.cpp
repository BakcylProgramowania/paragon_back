#include "example/Example.hpp"

namespace paragon {

Example::Example(const int sth) : sth{sth} {}

int Example::get() const {
    return sth;
}

}