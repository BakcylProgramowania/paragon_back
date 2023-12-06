#include "api/Api.hpp"

namespace paragon {

Api::Api(const int sth) : sth{sth} {}

int Api::get() const {
    return sth;
}

}