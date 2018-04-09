#pragma once
#include <functional>

template <class T> class hash_family {
	public:
		uint64_t hash(T elem);
};

template<class T>
inline uint64_t hash_family<T>::hash(T elem)
{
	return uint64_t();
}
