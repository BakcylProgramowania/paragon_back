#ifndef EnvironmentWrapper_hpp
#define EnvironmentWrapper_hpp

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

#endif /* EnvironmentWrapper_hpp */
