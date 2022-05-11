#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "./lib/json/single_include/nlohmann/json.hpp"
#include "block.cpp"

using json = nlohmann::json;

class Blockchain {
private:
    int size;
    int difficulty;
    int reward;
    bool blockchainExists;
    bool pendingExists;
    std::string blockchainFile;
    std::string pendingFile;
    std::vector<Block> blockchain;
    std::vector<Transaction> pendingTransactions;

public:
    Blockchain();
    ~Blockchain();
    void init();
    void readFromPendingFile();
    void writeToPendingFile();
    void readFromBlockchainFile();
    void writeToBlockchainFile(Block& block);
    void clearPendingFile();
    void createTransaction(const std::string senderAddress_, const std::string receiverAddress_, const double amount_);
    void minePendingTransactions(const std::string rewardAddress);
    void addBlock(Block& block, const bool isWriting);
    double getBalance(const std::string address);
    bool isValid();
    void print();
};

#endif