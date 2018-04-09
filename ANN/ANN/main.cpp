#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <random>

#include "hash_family.h"

using namespace std;

#define M 4
#define N 1000

int main(int argc, char** argv) {

	/*ifstream infile("thefile.txt");
	bitset<M> es[N];

	string line;
	int i = 0;
	while (getline(infile, line))
	{
		bitset<M> e(line);
		es[i++] = e;
	}*/

	//random_device seeder;
	////then make a mersenne twister engine
	//mt19937 engine(seeder());
	////then the easy part... the distribution
	//uniform_int_distribution<int> dist(0, 10);
	////then just generate the integer like this:
	//int one = dist(engine);
	//int two = dist(engine);

	//cout << "first " << one << "second " << two;

	hash_family<bitset<M>> hf([](bitset<M>) { return 32; });

	bitset<M> bs("0101");

	uint32_t res = hf.hash(bs);

	cout << res;

	return 0;
}