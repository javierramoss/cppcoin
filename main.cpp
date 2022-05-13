#include <iostream>
#include <ctime>
#include <vector>

#include "keygen.hpp"
#include "blockchain.hpp"

//Sample cryptographic keys #1
//public key: 03acb20247769bbb3925d54ee017e2239f5c151647d7472300df163b2bc8568e0e
//private key: 2f5a1d1b4f414dc17bd2edd306a0ff531e8962502d3bd012f2eb6ec8b7376725

//Sample cryptographic keys #2
//public key: 02ccec41dada51d84371c3ddb15555dba308c758131948d50389f913019ae177f2
//private key: 39036983b251447014be0053e4d1862d2e656f4853c27d95aa7cce30db34d5c8

std::string getLine(const std::string message) {
    std::cout << message;
    std::string str;
    std::cin >> str;
    return str;
}

int main() {
    KeyGen keygen;
    Blockchain cppcoin;

    char ch;
    bool isRunning = true;

    while (isRunning) {
        std::cout << "\nCPPCOIN\n1. Generate new keys\n2. Create new transaction\n3. Mine cppcoin\n4. Check balance\n5. Check blockchain's validity\n6. Exit\nEnter an option: ";
        std::cin >> ch;

        switch (ch)
        {
        case '1':
            std::cout << "\nGenerating cryptographic keys..\n";
            try {
                keygen.generate();   
                std::cout << "Public key: " << keygen.getPublicKey() << std::endl;
                std::cout << "Private key: " << keygen.getPrivateKey() << std::endl;
            } catch (int i) {
                std::cout << "Failed to generate cryptographic keys\n";
            }
            break;
        case '2':
            std::cout << "\nCreating new transaction..\n";
            try {
                cppcoin.createTransaction(getLine("Enter your public key: "), getLine("Enter receiver address: "), std::stod(getLine("Enter amount: ")));
            } catch (int i) {
                std::cout << "Insufficient funds to perform transaction\n";
            }
            break;
        case '3':
            std::cout << "\nStarting mining operation..\n";
            cppcoin.minePendingTransactions(getLine("Enter your public key: "));
            break;
        case '4':
            std::cout << "\nCheck balance..\n";
            std::cout << "Balance: " << cppcoin.getBalance(getLine("Enter your public key: ")) << std::endl;
            break;
        case '5':
            std::cout << "\nChecking blockchain validity..\n";
            std::cout << cppcoin.isValid() << std::endl;
            break;
        case '6':
            isRunning = false;
        default:
            break;
        }
    }

    return 0;
}