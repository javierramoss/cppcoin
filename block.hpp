#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "./lib/hash-library/sha256.cpp"
#include "transaction.cpp"

class Block {
private:
    std::string curHash;
    std::string prevHash;
    std::string timestamp;
    int nonce;

public:
    std::vector<Transaction> transactions;

    Block(std::vector<Transaction> transactions_);

    std::string computeHash();
    void mine(int difficulty);
    std::string stringify();
    bool isHashValid();
    bool areTransactionsValid();
    std::string getPrevHash() const;
    void setPrevHash(const std::string prevHash_);
    std::string getCurHash() const;
    void setCurHash(const std::string curHash_);
    std::string getTimestamp() const;
    void setTimestamp(const std::string timestamp_);
    int getNonce() const;
    void setNonce(const int nonce_);
};

#endif