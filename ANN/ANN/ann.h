#pragma once
#include <vector>
#include <functional>
#include <sparsepp/spp.h>

//#define SPP_USE_SPP_ALLOC 1

using spp::sparse_hash_map;
using namespace std;

template <class T, class S> class ann {
	private:
		vector<S> hfs;
		vector<sparse_hash_map<uint32_t, vector<T*>>> buckets;
		function<int(T, T)> dist;
	public:
		T query(T elem);
		void init(vector<T>* ps);

		ann(vector<S>* hash_family, function<int(T, T)> distance, int l) {
			hfs = *hash_family;
			dist = distance;
			buckets = vector<sparse_hash_map<uint32_t, vector<T*>>>(l);
		}
};

template<class T, class S>
T ann<T,S>::query(T elem)
{
	vector<T*> neighbors;

	for (size_t i = 0; i < hfs.size(); i++)
	{
		uint32_t hash = hfs[i].hash(elem);
		//vector<T*> nbs = buckets[i][hash];

		neighbors.insert(neighbors.end(), buckets[i][hash].begin(), buckets[i][hash].end());
	}

	T nearest;
	auto dis = INT32_MAX;

	for (auto neighbor : neighbors)
	{
		T n = *neighbor;
		auto d = dist(n, elem);
		if(d < dis)
		{
			nearest = n;
			dis = d;
		}
	}

	return nearest;
}

template<class T, class S>
void ann<T,S>::init(vector<T>* ps)
{
	auto count = 1;
	vector<T>& pst = *ps;
	for (size_t i = 0; i < hfs.size(); ++i)
	{
		for (size_t j = 0; j < pst.size(); ++j)
		{
			uint32_t hash = hfs[i].hash(pst[j]);

			if (buckets[i].count(hash) == 0)
			{
				buckets[i].insert(make_pair(hash, vector<T*>{ &pst[j] }));
			}
			else
			{
				buckets[i][hash].push_back(&pst[j]);
			}
		}

		cout << "Hash tables made: " << count++ << "\n";
	}
}
