#include "token.hpp"

std::string Token::createToken(const std::string& username, const std::string& email) {
    std::string input = username + email;

    // Inicjalizacja struktury MD5
    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    // Aktualizacja kontekstu MD5 danymi wejściowymi
    MD5_Update(&md5Context, input.c_str(), input.length());

    // Uzyskanie wyniku
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5_Final(digest, &md5Context);

    // Konwersja wyniku na stringa szesnastkowego
    std::stringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }

    return ss.str();
}
