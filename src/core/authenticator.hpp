#ifndef AUTHENTICATOR_HPP
#define AUTHENTICATOR_HPP

#include <string>

class Authenticator {
public:
    bool authenticateUser(const std::string& username, const std::string& password) const;
};

#endif