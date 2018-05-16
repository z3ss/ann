#pragma once
#include <string>

using chunk_t = unsigned long;
const static uint32_t chunk_size = 8 * sizeof(chunk_t);

class my_bitset
{
public:
	my_bitset(const std::string& bits);
	my_bitset(const size_t dimensions);
	my_bitset(const my_bitset& b);
	~my_bitset();

	my_bitset& operator=(const my_bitset& b)
	{
		const auto tmp_buffer = new chunk_t[buffer_size];
		memcpy(tmp_buffer, b.buffer, buffer_size * sizeof(chunk_t));
		delete[] buffer;
		buffer = tmp_buffer;
		return *this;
	}

	std::string to_string() const;
	size_t count() const;
	uint8_t bit(size_t idx) const;
	size_t get_dimension() const;

	my_bitset operator^(const my_bitset &other) const;

	size_t dimension, buffer_size;
	chunk_t* buffer;
};

