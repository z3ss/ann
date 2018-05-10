#include "sim_hash.h"



sim_hash::sim_hash(const std::vector<float>& hyperplanes)
{
	this->hyperplanes = hyperplanes;
}


sim_hash::~sim_hash()
= default;

uint32_t sim_hash::hash(std::vector<float>& elem)
{

}
