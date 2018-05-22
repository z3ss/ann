#pragma once
#include <vector>
#include <functional>
#include <forward_list>

#define SPP_USE_SPP_ALLOC 1

#include <sparsepp/spp.h>

using spp::sparse_hash_map;
using namespace std;

template <class T, class S, class L> class ann {
	private:
		vector<S> hfs;
		vector<sparse_hash_map<uint32_t, forward_list<T*>>> buckets;
		function<L(T, T)> dist;
	public:
		T query(T elem);
		void init(vector<T>* ps);

		ann(vector<S>* hash_family, function<L(T, T)> distance, int l) {
			hfs = *hash_family;
			dist = distance;
			buckets = vector<sparse_hash_map<uint32_t, forward_list<T*>>>(l);
		}
};

template<class T, class S, class L>
T ann<T,S,L>::query(T elem)
{
	vector<T*> neighbors;

	for (size_t i = 0; i < hfs.size(); i++)
	{
		uint32_t hash = hfs[i].hash(elem);
		//vector<T*> nbs = buckets[i][hash];

		//cout << buckets[i][hash].size() << " ";

		neighbors.insert(neighbors.end(), buckets[i][hash].begin(), buckets[i][hash].end());
	}

	cout << "\n";

	cout << neighbors.size() << "\n";

	T* nearest = nullptr;
	L dis = 100000;

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

	if (nearest == nullptr) return  elem;

	return *nearest;
}

template<class T, class S, class L>
void ann<T,S,L>::init(vector<T>* ps)
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
				buckets[i].insert(make_pair(hash, forward_list<T*>{ &pst[j] }));
			}
			else
			{
				existing++;
				buckets[i][hash].push_front(&pst[j]);
			}

		}

		cout << existing << " " << new_table << "\n";
		cout << "Hash tables made: " << count++ << "\n";
	}
}
