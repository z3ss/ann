#include "sim_hash.h"
#include <numeric>

using namespace std;

sim_hash::sim_hash(const vector<vector<float>>& hyperplanes)
{
	this->hyperplanes = hyperplanes;
}


sim_hash::~sim_hash()
= default;

uint32_t sim_hash::hash(vector<float>& elem)
{
	uint32_t res = 0;

	for (auto hp : hyperplanes)
	{
		const auto ip = inner_product(begin(hp), end(hp), begin(elem), 0.0);
		if (ip >= 0)
		{
			res <<= 1;
		}
		else
		{
			res <<= 0;
		}
	}

	return res;
}
