#pragma once
#include <vector>
#include <Eigen/StdVector>

using namespace std;

class sim_hash
{
	private:
		vector<Eigen::VectorXf> hyperplanes;
	public:
		sim_hash(const vector<Eigen::VectorXf>& hyperplanes);
		~sim_hash();
		uint32_t hash(Eigen::VectorXf& elem);
};

