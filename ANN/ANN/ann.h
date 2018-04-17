#pragma once
#include <unordered_set>
#include <map>
#include <vector>
#include <functional>

using namespace std;

template <class T, class S> class ann {
	private:
		vector<S> hfs;
		vector<map<uint32_t, vector<T>>> buckets;
		function<int(T, T)> dist;
	public:
		T query(T elem);
		void init(vector<T>& ps);

		ann(vector<S> hash_family, function<int(T, T)> distance) {
			hfs = hash_family;
			dist = distance;
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
void ann<T,S>::init(vector<T>& ps)
{
	vector<map<uint32_t, vector<T>>> maps;
	auto count = 0;
	for (S hf : hfs)
	{
		cout << "Hash tables made: " << count++ << "\n";
		map<uint32_t, vector<T>> m;

		for (T p : ps)
		{
			uint32_t hash = hf.hash(p);

			if(m.count(hash) == 0)
			{
				vector<T> v = { p };
				m.insert(make_pair(hash, v));
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
