#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

#define M 128
#define N 1000

int main(int argc, char** argv) {

	ifstream infile("thefile.txt");
	bitset<M> es[N];

	string line;
	int i = 0;
	while (getline(infile, line))
	{
		bitset<M> e(line);
		es[i++] = e;
	}



	return 0;
}