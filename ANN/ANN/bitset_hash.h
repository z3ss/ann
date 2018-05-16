#pragma once
#include <bitset>
#include <vector>
#include "my_bitset.h"

using namespace std;

class bitset_hash
{
	private:
		vector<int> bits;
	public:
		bitset_hash(const vector<int>& bits);
		~bitset_hash();
		uint32_t hash(my_bitset& elem);
};

