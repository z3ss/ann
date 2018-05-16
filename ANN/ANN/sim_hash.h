#pragma once
#include <vector>

using namespace std;

class sim_hash
{
	private:
		vector<vector<float>> hyperplanes;
	public:
		sim_hash(const vector<vector<float>>& hyperplanes);
		~sim_hash();
		uint32_t hash(std::vector<float>& elem);
};

