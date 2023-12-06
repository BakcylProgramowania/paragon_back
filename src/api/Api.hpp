#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/component.hpp"

namespace paragon {

class Api {
public:
explicit Api(const int sth);
int get() const;

private:
int sth{};
};

}