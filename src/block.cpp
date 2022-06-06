#include <iostream>
#include <string>

#include "./easy-ecc/ecc.c"
#include "./hash-library/sha256.cpp"
#include "block.hpp"

Block::Block(std::vector<Transaction> transactions_) {
    transactions = transactions_;
    nonce = 0;
}

std::string Block::computeHash() {
    SHA256 sha256;
    return sha256(timestamp + stringify() + prevHash + std::to_string(nonce));
}

void Block::mine(int difficulty) {
    std::string str(difficulty, '0');
    //int temp = 0;
    while (curHash.substr(0, difficulty) != str) {
        nonce++;
        curHash = computeHash();
    }
    //nonce = std::to_string(temp);
    if (prevHash != "0")
        std::cout << "Block mined: " << curHash << std::endl;
}

std::string Block::stringify() {
    std::string str = "";
    for (size_t i = 0; i < transactions.size(); i++) {
        str += transactions[i].computeHash();//.stringify();
    }
    return str;
}

bool Block::isHashValid() {
    return computeHash() == curHash;
}

bool Block::areTransactionsValid() {
    for (size_t i = 0; i < transactions.size(); i++) {
        if(!transactions[i].isValid())
            return false;
    }
    return true;
}

std::string Block::getPrevHash() const {
    return prevHash;
}

void Block::setPrevHash(const std::string prevHash_) {
    prevHash = prevHash_;
}

std::string Block::getCurHash() const {
    return curHash;
}

void Block::setCurHash(const std::string curHash_) {
    curHash = curHash_;
}

std::string Block::getTimestamp() const {
    return timestamp;
}

void Block::setTimestamp(const std::string timestamp_) {
    timestamp = timestamp_;
}

int Block::getNonce() const {
    return nonce;
}

void Block::setNonce(const int nonce_) {
    nonce = nonce_;
}