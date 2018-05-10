#pragma once
#include <vector>

class sim_hash
{
	private:
		std::vector<float> hyperplanes;
	public:
		sim_hash(const std::vector<float>& hyperplanes);
		~sim_hash();
		uint32_t hash(std::vector<float>& elem);
};

