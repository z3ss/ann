#pragma once
#include <vector>
#include <functional>

#define SPP_USE_SPP_ALLOC 1

#include <sparsepp/spp.h>

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

		cout << buckets[i][hash].size() << " ";

		neighbors.insert(neighbors.end(), buckets[i][hash].begin(), buckets[i][hash].end());
	}

	cout << "\n";

	cout << neighbors.size() << "\n";

	T* nearest = nullptr;
	auto dis = INT32_MAX;

	for (T* neighbor : neighbors)
	{
		//T n = *neighbor;
		auto d = dist(*neighbor, elem);
		if(d < dis)
		{
			nearest = neighbor;
			dis = d;
		}
	}

	neighbors.clear();

	return *nearest;
}

template<class T, class S>
void ann<T,S>::init(vector<T>* ps)
{
	auto count = 1;
	vector<T>& pst = *ps;
	
	for (size_t i = 0; i < hfs.size(); ++i)
	{
		auto new_table = 0;
		auto existing = 0;
		for (size_t j = 0; j < pst.size(); ++j)
		{
			uint32_t hash = hfs[i].hash(pst[j]);

			if (!buckets[i].contains(hash))
			{
				new_table++;
				buckets[i].insert(make_pair(hash, vector<T*>{ &pst[j] }));
			}
			else
			{
				existing++;
				buckets[i][hash].push_back(&pst[j]);
			}
		}

		cout << existing << " " << new_table << "\n";
		cout << "Hash tables made: " << count++ << "\n";
	}
}
