#pragma once
#include <unordered_map>
#include <vector>
#include <functional>

using namespace std;

template <class T, class S> class ann {
	private:
		vector<S> hfs;
		vector<unordered_map<uint32_t, vector<T>>> buckets;
		function<int(T, T)> dist;
	public:
		T query(T elem);
		void init(vector<T>* ps);

		ann(vector<S>* hash_family, function<int(T, T)> distance, int l) {
			hfs = *hash_family;
			dist = distance;
			buckets = vector<unordered_map<uint32_t, vector<T>>>(l);
		}
};

template<class T, class S>
T ann<T,S>::query(T elem)
{
	vector<T> neighbors;

	for (size_t i = 0; i < hfs.size(); i++)
	{
		uint32_t hash = hfs[i].hash(elem);
		vector<T> nbs = buckets[i][hash];

		neighbors.insert(neighbors.end(), nbs.begin(), nbs.end());
	}

	T nearest;
	auto dis = INT32_MAX;

	for (auto neighbor : neighbors)
	{
		auto d = dist(neighbor, elem);
		if(d < dis)
		{
			nearest = neighbor;
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
		//map<uint32_t, vector<T>> m;

		for (size_t j = 0; j < pst.size(); ++j)
		{
			uint32_t hash = hfs[i].hash(pst[j]);

			if (buckets[i].count(hash) == 0)
			{
				buckets[i].insert(make_pair(hash, vector<T>{ pst[j] }));
			}
			else
			{
				buckets[i][hash].push_back(pst[j]);
			}
		}

		//buckets.push_back(m);

		cout << "Hash tables made: " << count++ << "\n";
	}
}
