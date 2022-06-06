#include "keygen.hpp"

KeyGen::KeyGen() {

}

KeyGen::~KeyGen() {

}

void KeyGen::generate() {
    if (!ecc_make_key(publicKey, privateKey))
        throw -1;
}

std::string KeyGen::uint8_to_hex(const uint8_t *v, const size_t s) {
  std::stringstream ss;

  ss << std::hex << std::setfill('0');

  for (size_t i = 0; i < s; i++) {
    ss << std::hex << std::setw(2) << static_cast<int>(v[i]);
  }

  return ss.str();
}

uint8_t* KeyGen::hex_to_uint8(uint8_t *dest, size_t count, const char *src) {
    int value;
    for (size_t i = 0; i < count && sscanf(src + i * 2, "%2x", &value) == 1; i++) {
        dest[i] = value;
    }
    return dest;
}

std::string KeyGen::getPublicKey() const {
    return uint8_to_hex(publicKey, ECC_BYTES+1);
}

std::string KeyGen::getPrivateKey() const {
    return uint8_to_hex(privateKey, ECC_BYTES);
}