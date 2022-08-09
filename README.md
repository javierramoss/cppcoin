# cppcoin
cppcoin is an educational implementation of a cryptocurrency using C++. It is not meant to provide a reliable system to transfer value nor generating cryptographic keys for real life use cases.

## Features
- Simple to use menu using the command line
- Create ECC public and private keys
- Transfer money to and from local cppcoin addresses
- Transactions performed on the blockchain are saved in the host's machine

## Installation
1. Clone the repo:
```
git clone --recurse-submodules -j8 https://github.com/javierramoss/cppcoin.git
```
2. cd into the cppcoin folder
3. Remove line 11 from `./lib/hash-library/sha256.cpp`
4. Create a bin folder
5. Compile using the command:
```
make
```

## Usage
1. Click on the executable `cppcoin.exe` or use the command:
```
cppcoin.exe
```
![menu](https://user-images.githubusercontent.com/65036152/183533608-889c8c9d-3a34-4866-a556-5f7367880cc6.JPG)

2. Select option 1 to generate a new pair of public and private keys

![a1](https://user-images.githubusercontent.com/65036152/183533763-a97cf256-3a21-47c3-b89c-2a57ef567b28.JPG)

3. Use the keys to mine blocks or transfer cppcoins

## Explanation
The blockchain starts off by mining the genesis block and adding it to the ledger saved to `blockchain.txt`. A block contains an id, nonce, previous block, time of creation, and transactions if any. Since it is the first block, no transfer transactions have been performed and the previous block is "0".

![b1](https://user-images.githubusercontent.com/65036152/183533047-f9cd9db5-df10-41bf-ad7e-9fda4cff773c.JPG)

Address A mines a block for the first time, the block is immediately pushed to the blockchain but the reward coins will be pushed in the next mined block's transactions,

![a3](https://user-images.githubusercontent.com/65036152/183533147-9a552c5a-4397-46a5-b9c4-d67f00b39816.JPG)

![block2](https://user-images.githubusercontent.com/65036152/183534479-4182e793-6873-4060-a1c3-615b1c21e513.JPG)

Address A mines another block, making the first 100 cppcoin reward for the first mined block available in their balance.

![block3](https://user-images.githubusercontent.com/65036152/183534548-af20e286-ff9c-4e2d-be75-23b8c531c38b.JPG)

Address A transfers 50 cppcoins to Address B, then Address A mines another block so the transaction is pushed with this block. Now the 50 cppcoins transaction is contained in this block along with the 100 cppcoin reward from the second block mined.

![a2](https://user-images.githubusercontent.com/65036152/183533541-77f625e4-b0c3-465b-abf1-872f433bcf23.JPG)

![b3](https://user-images.githubusercontent.com/65036152/183535778-7f40ea8d-aafc-4ec1-83cc-97df1db7197f.JPG)

Now Address A's balance is 150 cppcoins and Address B's is 50 cppcoins.

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b NewBranch`)
3. Commit your Changes (`git commit -m 'Add x'`)
4. Push to the Branch (`git push origin NewBranch`)
5. Open a Pull Request

## License

Distributed under the MIT License. See `LICENSE` for more information.   
