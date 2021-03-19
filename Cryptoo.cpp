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
	return generateHash() == blockHash ;

}




class Blockchain
{
private:
	Block createGenesisBlock();

public:

	vector<Block> chain;
	Blockchain();
	void addBlock(TransactionData data);
	bool isChainValid();

	Block* getLatestBlock();


};


Blockchain::Blockchain()
{
	Block genesis = createGenesisBlock();
	chain.push_back(genesis);

}


Block Blockchain::createGenesisBlock()
{
	time_t current;
	TransactionData d;
	d.amount = 0;
	d.receiverKey = "None";
	d.senderKey = "None";
	d.timestamp = time(&current);

	hash<int> hash1;
	Block genesis(0, d, hash1(0));
	return genesis;

}

Block *Blockchain::getLatestBlock()
{
	return &chain.back();
}

void Blockchain::addBlock(TransactionData d)
{

	int index = (int)chain.size() - 1;
	Block newBlock(index, d, getLatestBlock()->getHash());

}

bool Blockchain::isChainValid()
{

	vector <Block>::iterator it;
	int chainLen = (int)chain.size();

	for (it = chain.begin(); it != chain.end(); ++it)
	{
		Block currentBlock = *it;
		if (!currentBlock.isHashVallid())
		{
			return false;

		}
		if (chainLen > 1)
		{
			Block previousBlock = *(it - 1);
			if (currentBlock.getPreviousHash() != previousBlock.getHash())
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	Blockchain PotatoCoin;


	TransactionData data1;
	time_t data1Time;
	data1.amount = 1.5;
	data1.receiverKey = "JohnDoe";
	data1.senderKey = "Potato";
	data1.timestamp = time(&data1Time);
}

