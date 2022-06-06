#include "transaction.hpp"

Transaction::Transaction(const std::string senderAddress_, const std::string receiverAddress_, const double amount_) {
    senderAddress = senderAddress_;
    receiverAddress = receiverAddress_;
    amount = amount_;
}

std::string Transaction::computeHash() {
    SHA256 sha256;
    return sha256(senderAddress + receiverAddress + std::to_string(amount));
}

void Transaction::sign(const std::string privateHex) {
    uint8_t privateKey[ECC_BYTES+1];
    KeyGen::hex_to_uint8(privateKey, ECC_BYTES+1, privateHex.c_str());
    
    uint8_t hash[ECC_BYTES*2];
    KeyGen::hex_to_uint8(hash, ECC_BYTES*2, computeHash().c_str());

    if (!ecdsa_sign(privateKey, hash, signature))
        std::cout << "Error signing transaction\n";
}

bool Transaction::isValid() {
    if (senderAddress == "")
        return true;
    if (!signature)
        std::cout << "no signature!" << std::endl;

    //sender hex to uint8_t
    uint8_t sender[ECC_BYTES+1];
    KeyGen::hex_to_uint8(sender, ECC_BYTES+1, senderAddress.c_str());

    //transaction hex to uint8_t
    uint8_t hash[ECC_BYTES*2];
    KeyGen::hex_to_uint8(hash, ECC_BYTES*2, computeHash().c_str());

    return ecdsa_verify(sender, hash, signature);
}

std::string Transaction::stringify() {
    std::string str = senderAddress + receiverAddress + std::to_string(amount);
    return str;
}

std::string Transaction::getSenderAddress() const {
    return senderAddress;
}

std::string Transaction::getReceiverAddress() const {
    return receiverAddress;
}

double Transaction::getAmount() const {
    return amount;
}