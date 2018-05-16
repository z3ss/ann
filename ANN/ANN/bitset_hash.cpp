#include "bitset_hash.h"
#include <bitset>
#include <iostream>

using namespace std;

bitset_hash::bitset_hash(const vector<int>& bits)
{
	this->bits = bits;
}

bitset_hash::~bitset_hash()
= default;

uint32_t bitset_hash::hash(my_bitset& elem)
{
	uint32_t hash = 0;

	for (auto bit : bits)
	{
		const auto b = elem.bit(bit);
		hash += b;
		hash <<= 1;
	}

	hash >>= 1;

	return hash;
}
