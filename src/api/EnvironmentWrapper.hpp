#pragma once

#include "oatpp/network/Server.hpp"

class EnvironmentWrapper {
public:
    EnvironmentWrapper() {
        oatpp::base::Environment::init();
    }

    ~EnvironmentWrapper() {
        oatpp::base::Environment::destroy();
    }
};
