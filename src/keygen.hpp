#ifndef KEYGEN_HPP
#define KEYGEN_HPP

#include <sstream>
#include <iomanip>
#include "./easy-ecc/ecc.h"
#include "./hash-library/sha256.h"

class KeyGen {
private:
    uint8_t publicKey[ECC_BYTES+1];
    uint8_t privateKey[ECC_BYTES];

public:
    KeyGen();
    ~KeyGen();
    void generate();
    std::string getPublicKey() const;
    std::string getPrivateKey() const;
    static std::string uint8_to_hex(const uint8_t *v, const size_t s);
    static uint8_t* hex_to_uint8(uint8_t *dest, size_t count, const char *src);
};

#endif