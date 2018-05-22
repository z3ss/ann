#include "sim_hash.h"

using namespace std;

sim_hash::sim_hash(const vector<Eigen::VectorXf>& hyperplanes)
{
	this->hyperplanes = hyperplanes;
}


sim_hash::~sim_hash()
= default;

uint32_t sim_hash::hash(Eigen::VectorXf& elem)
{
	uint32_t res = 0;

	for (const auto& hp : hyperplanes)
	{
		const auto ip = hp.dot(elem);
		if (ip >= 0)
		{
			res++;
		}

		res <<= 1;
	}

	return res;
}
