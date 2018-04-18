#include "bitset_hash.h"

using namespace std;

bitset_hash::bitset_hash(const vector<int> bits)
{
	this->bits = bits;
}


bitset_hash::~bitset_hash()
= default;

uint32_t bitset_hash::hash(bitset<128>* elem)
{
	uint32_t hash = 0;

	for (auto bit : bits)
	{
		hash += (*elem)[bit];
		hash <<= 1;
	}

	return hash;
}
