#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <random>
#include <vector>

#include "bitset_hash.h"
#include "ann.h"

using namespace std;

#define M 128
#define K 16
#define L 20
#define N 1000

int dist(bitset<M> a, bitset<M> b)
{
	auto dif = a ^ b;
	return dif.count();
}

vector<bitset_hash> create_bitset_hash()
{
	random_device seeder;
	//then make a mersenne twister engine
	mt19937 engine(seeder());
	//then the easy part... the distribution
	const uniform_int_distribution<int> rand_dist(0, M-1);

	vector<bitset_hash> hfs;

	for(size_t i = 0; i < L; i++)
	{
		vector<int> bits;

		for (size_t j = 0; j < K; j++)
		{
			const auto bit = rand_dist(engine);
			bits.push_back(bit);
		}

		bitset_hash bh(bits);
		
		hfs.push_back(bh);
	}

	return hfs;
}

int main(int argc, char** argv) {

	cout << "loading file... ";

	ifstream infile("nytimes.hamming.128.data");
	vector<bitset<M>> es;

	string line;
	while (getline(infile, line))
	{
		es.emplace_back(line);
	}

	cout << es.size() << " elements loaded\n";

	auto hfs = create_bitset_hash();

	ann<bitset<M>,bitset_hash> alg(&hfs, dist, L);

	alg.init(&es);

	cout << "query: 00110010001110000101110111011100001110011110011010010010111011101010100101011111100000010100010101111100011111001001111110101011 \n";

	bitset<M> q("00110010001110000101110111011100001110011110011010010010111011101010100101011111100000010100010101111100011111001001111110101011");

	auto res = alg.query(q);

	cout << "found: " << res.to_string() << "\n";

	cout << "distance: " << dist(q, res);

	return 0;
}