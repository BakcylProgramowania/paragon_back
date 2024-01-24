#pragma once

#include <iomanip>
#include <openssl/md5.h>
#include <string>

class Token {
 public:
  std::string createToken(const std::string& username,
                          const std::string& email);
};