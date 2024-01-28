#include "token.hpp"

#include <openssl/rand.h>

#include <boost/uuid/uuid_io.hpp>

std::string TokenGenerator::generateToken(const std::string& username,
                                          const std::string& email) const {
  unsigned char randomChars[16];
  RAND_bytes(randomChars, sizeof(randomChars));

  std::string input(reinterpret_cast<char*>(randomChars), sizeof(randomChars));
  input += username + email;

  boost::uuids::random_generator generator;
  boost::uuids::uuid uuid = generator();

  return boost::uuids::to_string(uuid);
}