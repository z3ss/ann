#pragma once
#include <functional>

template <class T> class hash_family {
	private:
		std::function<uint32_t(T)> hash_function;
	public:
		uint32_t hash(T elem);
		hash_family(std::function<uint32_t(T)> hfunc) {
			hash_function = hfunc;
		}
};

template<class T>
inline uint32_t hash_family<T>::hash(T elem)
{
	return hash_function(elem);
}
