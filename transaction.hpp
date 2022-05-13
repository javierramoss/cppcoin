#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <iostream>
#include <sstream>
#include "keygen.hpp"
#include "./lib/hash-library/sha256.h"

class Transaction {
private:
    std::string senderAddress;
    std::string receiverAddress;
    double amount;

    uint8_t signature[ECC_BYTES*2];

public:
    Transaction(const std::string senderAddress_, const std::string receiverAddress_, const double amount_);
    std::string computeHash();
    void sign(const std::string privateHex);
    bool isValid();
    std::string stringify();
    std::string getSenderAddress() const;
    std::string getReceiverAddress() const;
    double getAmount() const;
};

#endif