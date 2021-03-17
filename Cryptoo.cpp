#include <ctime>
#include <vector>
#include <string>

using namespace std;


struct TransactionData {
	double amount;
	string senderKey;
	string receiverKey;
	time_t timestamp;
};

class Block
{
	private:
		int index;
		size_t blockHash;
		size_t previousHash;
		size_t generateHash();
	
	
	public:

		Block(int idx, TransactionData d, size_t prevHash);
		size_t getHash();


		size_t getPreviousHash();

		TransactionData data;

		bool isHashVallid();



};

Block::Block(int idx, TransactionData d, size_t prevHash)
{
	index = idx;
	data = d;
	previousHash = prevHash;
	blockHash = generateHash();

}

size_t Block::generateHash()
{
	hash<string> hash1;
	hash<size_t> hash2;
	hash<size_t> finalHash;
	string toHash = to_string(data.amount) + data.receiverKey + data.senderKey + to_string(data.timestamp);

	return finalHash(hash1(toHash) + hash2(previousHash));

};

size_t Block::getHash()
{
	return blockHash;


}

size_t Block::getPreviousHash()
{
	return previousHash;


}

bool Block::isHashVallid()
{
	return generateHash;

}




class Blockchain
{
private:
	Block createGenesisBlock();

public:

	vector<Block> chain;
	Blockchain();
	void addBlock(TransactionData data);
	void isChainValid();

	Block* getLatestBlock();


};
