#pragma once
#include <unordered_set>
#include <map>
#include <vector>

#include "hash_family.h"

using namespace std;

template <class T> class ann {
	private:
		vector<hash_family<T>> hfs;
		vector<map<uint32_t, vector<T>>> buckets;
	public:
		T query(T elem);
		void init(vector<T> ps);

		ann(vector<hash_family<T>> hash_family) {
			hfs = hash_family;
		}
};

template<class T>
T ann<T>::query(T elem)
{
	vector<T> neighbors;

	for (size_t i = 0; i < hfs.size(); i++)
	{
		vector<T> nbs = buckets[i][hfs[i].hash(elem)];

		neighbors.insert(neighbors.end(), nbs.begin(), nbs.end());
	}

	T nearest;
	auto dis = INT32_MAX;

	for (auto neighbor : neighbors)
	{
		
	}

	return elem;
}

template<class T>
void ann<T>::init(vector<T> ps)
{
	vector<map<uint32_t, vector<T>>> maps;

	for (hash_family<T> hf : hfs)
	{
		map<uint32_t, vector<T>> m;

		for (T p : ps)
		{
			uint32_t hash = hf.hash(p);

			if(m.count(hash) == 0)
			{
				vector<T> v = { p };
				m.insert(hash, v);
			}
			else
			{
				m[hash].push_back(p);
			}
		}

		maps.push_back(m);
	}

	buckets = maps;
}
