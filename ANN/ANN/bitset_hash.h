#pragma once
#include <bitset>
#include <vector>

using namespace std;

class bitset_hash
{
	private:
		vector<int> bits;
	public:
		bitset_hash(const vector<int>& bits);
		~bitset_hash();
		uint32_t hash(bitset<128>& elem);
};

