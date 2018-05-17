#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <random>
#include <vector>

#include "bitset_hash.h"
#include "ann.h"
#include "sim_hash.h"
#include "my_bitset.h"

using namespace std;

#define M 128
#define K 16
#define L 60
#define N 1000

int dist(const my_bitset& a, const my_bitset& b)
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

vector<sim_hash> create_sim_hash()
{
	random_device seeder;
	//then make a mersenne twister engine
	mt19937 engine(seeder());
	//then the easy part... the distribution
	normal_distribution<float> rand_dist;

	vector<sim_hash> hfs;

	for (size_t i = 0; i < L; i++)
	{
		vector<vector<float>> vs(K);
		for (int l = 0; l < M; ++l)
		{
			vector<float> v;

			for (size_t j = 0; j < K; j++)
			{
				const auto d = rand_dist(engine);
				v.push_back(d);
			}

			vs.push_back(v);
		}

		const sim_hash bh(vs);

		hfs.push_back(bh);
	}

	return hfs;
}

//int main(int argc, char** argv) {
//
//	cout << "loading file... ";
//
//	ifstream infile("nytimes.hamming.128.data");
//	vector<my_bitset> es;
//
//	string line;
//	while (getline(infile, line))
//	{
//		es.emplace_back(line);
//	}
//
//	cout << es.size() << " elements loaded\n";
//
//	/*bitset<M> q("00110010001110000101110111011100001110011110011010010010111011101010100101011111100000010100010101111100011111001001111110101011");
//	int min = -1;
//
//	for (size_t i = 0; i < es.size(); i++)
//	{
//		auto d = dist(q, es[i]);
//		if (min < 0 || d < min)
//		{
//			min = d;
//			cout << es[i].to_string() << " dist: " << d << "\n";
//		}
//	}*/
//
//	auto hfs = create_bitset_hash();
//
//	ann<my_bitset,bitset_hash> alg(&hfs, dist, L);
//
//	alg.init(&es);
//
//	cout << "query: 00110010001110000101110111011100001110011110011010010010111011101010100101011111100000010100010101111100011111001001111110101011 \n";
//
//	const my_bitset q("00110010001110000101110111011100001110011110011010010010111011101010100101011111100000010100010101111100011111001001111110101011");
//
//	auto res = alg.query(q);
//
//	cout << "found: " << res.to_string() << "\n";
//
//	cout << "distance: " << dist(q, res);
//
//	return 0;
//}

int main()
{
	cout << "loading file... ";

	ifstream infile("nytimes.hamming.128.data");
	vector<vector<float>> es;

	const string delimiter = " ";
	string line;
	while (getline(infile, line))
	{
		vector<float> plane(M);
		size_t pos = 0;
		while ((pos = line.find(delimiter) != string::npos))
		{
			const string tmp = line.substr(0, pos);
			plane.push_back(stof(tmp));
			line.erase(0, pos + delimiter.length());
		}
		es.push_back(plane);
	}

	cout << es.size() << " elements loaded\n";
}