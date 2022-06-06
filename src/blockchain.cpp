#include "blockchain.hpp"

Blockchain::Blockchain() {
    size = 0;
    difficulty = 4;
    reward = 100;
    blockchainExists = true;
    pendingExists = false;
    blockchainFile = "blockchain.txt";
    pendingFile = "pending.txt";
    init();
}

Blockchain::~Blockchain() {
    writeToPendingFile();
    if (pendingTransactions.size() < 1)
        clearPendingFile();
}

void Blockchain::init() {
    std::ifstream in(blockchainFile);
    blockchainExists = (in && in.peek() != std::ifstream::traits_type::eof());
    in.close();

    if (!blockchainExists) {
        Block block(pendingTransactions);
        addBlock(block, false);
        writeToBlockchainFile(block);
        blockchainExists = true;
    }
    else {
        readFromBlockchainFile();
        readFromPendingFile();
        clearPendingFile();
    }
}

void Blockchain::readFromPendingFile() {
    json j = json::array();
    std::ifstream in(pendingFile);
    pendingExists = (in && in.peek() != std::ifstream::traits_type::eof());

    if (pendingExists) {
        j = json::parse(in);
        for (auto& transaction : j)
            pendingTransactions.push_back(Transaction(transaction["sender"], transaction["receiver"], transaction["amount"]));
    }
    in.close();
}

void Blockchain::writeToPendingFile() {
    json j = json::array();
    std::ifstream in(pendingFile);
    if (pendingExists)
        j = json::parse(in);
    
    for (size_t i = 0; i < pendingTransactions.size(); i++) {
        j.push_back({
            {"sender", pendingTransactions[i].getSenderAddress()},
            {"receiver", pendingTransactions[i].getReceiverAddress()},
            {"amount", pendingTransactions[i].getAmount()}
        });
    }
    in.close();
    
    std::ofstream out(pendingFile);
    out << std::setw(4) << j << std::endl;
    out.close();
}

void Blockchain::clearPendingFile() {
    std::ofstream out(pendingFile, std::ofstream::out | std::ofstream::trunc);
    out.close();
    pendingExists = false;
}

void Blockchain::readFromBlockchainFile() {
    json j = json::array();
    std::ifstream in(blockchainFile);
    if (blockchainExists) {
        j = json::parse(in);

        for (auto& block : j) {
            std::vector<Transaction> transactions;
            for (auto& transaction : block["transactions"])
                transactions.push_back(Transaction(transaction["sender"], transaction["receiver"], transaction["amount"]));

            Block temp(transactions);
            temp.setCurHash(block["block"]);
            temp.setPrevHash(block["previous"]);
            temp.setTimestamp(block["time"]);
            temp.setNonce(block["nonce"].get<int>());
            blockchain.push_back(temp);
            size++;
        }
    }
    in.close();
}

void Blockchain::writeToBlockchainFile(Block& block) {
    json j = json::array();
    std::ifstream in(blockchainFile);
    if (blockchainExists)
        j = json::parse(in);
    
    json temp = {};
    for (size_t i = 0; i < block.transactions.size(); i++) {
        temp.push_back({
            {"sender", block.transactions[i].getSenderAddress()},
            {"receiver", block.transactions[i].getReceiverAddress()},
            {"amount", block.transactions[i].getAmount()}
        });
    }

    j.push_back({
        {"block", block.getCurHash()},
        {"previous", block.getPrevHash()},
        {"time", block.getTimestamp()},
        {"nonce", block.getNonce()},
        {"transactions", temp}
    });

    in.close();
    
    std::ofstream out(blockchainFile);
    out << std::setw(4) << j << std::endl;
    out.close();
}

void Blockchain::createTransaction(const std::string senderAddress_, const std::string receiverAddress_, const double amount_) {
    if (getBalance(senderAddress_) < amount_)
        throw -1;

    Transaction transaction(senderAddress_, receiverAddress_, amount_);

    std::cout << "Enter your private key: ";
    std::string str;
    std::cin >> str;
    transaction.sign(str);

    if (!transaction.isValid())
        std::cout << "invalid transaction cannot be added!\n";
    else
        pendingTransactions.push_back(transaction);
}

void Blockchain::minePendingTransactions(const std::string rewardAddress) {
    Block block(pendingTransactions);
    addBlock(block, true);
    writeToBlockchainFile(block);

    clearPendingFile();
    pendingTransactions.clear();
    pendingTransactions.push_back(Transaction("", rewardAddress, static_cast<double>(reward)));
}

void Blockchain::addBlock(Block& block, const bool isWriting) {
    size++;
    block.setTimestamp(std::to_string(std::time(0)));
    block.setPrevHash(size == 1 ? "0" : blockchain.back().getCurHash());
    block.mine(difficulty);
    blockchain.push_back(block);

    if (size != 1 && isWriting)
        std::cout << "Block mined!" << std::endl;
}

double Blockchain::getBalance(const std::string address) {
    double balance = 0;
    for (int i = 0; i < size; i++) {
        for (size_t j = 0; j < blockchain[i].transactions.size(); j++) {
            if (blockchain[i].transactions[j].getSenderAddress() == address)
                balance -= blockchain[i].transactions[j].getAmount();
            if (blockchain[i].transactions[j].getReceiverAddress() == address)
                balance += blockchain[i].transactions[j].getAmount();      
        }
    }
    return balance;
}

bool Blockchain::isValid() {
    if (size > 1) {
        for (int i = 1; i < size; i++) {
            Block prevBlock = blockchain[i - 1];
            Block curBlock = blockchain[i];

            if (!curBlock.areTransactionsValid())
                return false;
            if (curBlock.getCurHash() != curBlock.computeHash())
                return false;
            if (curBlock.getPrevHash() != prevBlock.getCurHash())
                return false;
        }
    }
    else {
        if (blockchain[0].getCurHash() != blockchain[0].computeHash() || blockchain[0].getPrevHash() != "0")
            return false;
    }

    return true;
}

void Blockchain::print() {
    json j = json::array();
    std::ifstream in(blockchainFile);
    if (blockchainExists)
        j = json::parse(in);
        
    std::vector<Block>::iterator it;
    for (it = blockchain.begin(); it != blockchain.end(); it++) {
        Block cur = *it;
        std::cout << "time: " << cur.getTimestamp() << std::endl;
        //std::cout << "amount: " << cur.amount << std::endl;
        std::cout << "prevHash: " << cur.getPrevHash() << std::endl;
        std::cout << "curHash: " << cur.getCurHash() << std::endl;
        //std::cout << "sender: " << cur.senderKey << std::endl;
        //std::cout << "receiver: " << cur.receiverKey << "\n" << std::endl;
    }
}