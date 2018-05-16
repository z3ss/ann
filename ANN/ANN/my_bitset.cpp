#include "my_bitset.h"
#include <intrin.h>
#include <algorithm>

using namespace std;

my_bitset::my_bitset(const size_t dimensions)
{
	dimension = dimensions;
	buffer_size = dimensions / chunk_size;

	if (dimensions%chunk_size != 0) buffer_size++;

	buffer = new chunk_t[buffer_size]{ 0 };
}

my_bitset::my_bitset(const my_bitset& b) : dimension(b.dimension), buffer_size(b.buffer_size), buffer(new chunk_t[buffer_size])
{
	memcpy(buffer, b.buffer, buffer_size * sizeof(chunk_t));
}

my_bitset::my_bitset(const std::string& bits) : my_bitset(bits.length())
{
	for (size_t i = 0; i < buffer_size; ++i)
	{
		chunk_t tmp = 0;
		const auto remains = min(chunk_size, dimension - i * chunk_size);
		for (size_t j = 0; j <  remains; ++j)
		{
			if (bits[i*chunk_size + j] == '1')
				tmp += 1 << j;
		}
		buffer[i] = tmp;
	}
}

my_bitset::~my_bitset()
{
	delete []buffer;
}

string my_bitset::to_string() const
{
	string s;
	for (size_t i = 0; i < dimension; ++i)
	{
		const auto idx = i / chunk_size;
		const auto is_set = (buffer[idx] & (1 << (i%chunk_size))) != 0;
		s += is_set ? '1' : '0';
	}

	return s;
}

size_t my_bitset::count() const
{
	size_t cnt = 0;

	for (size_t i = 0; i < buffer_size; ++i)
	{
		cnt += __popcnt(buffer[i]);
	}

	return cnt;
}

uint8_t my_bitset::bit(const size_t idx) const
{
	const auto pos = idx / chunk_size;
	const auto offset = idx % chunk_size;
	return (buffer[pos] & (1 << offset)) != 0 ? 1 : 0;
}

size_t my_bitset::get_dimension() const
{
	return dimension;
}

my_bitset my_bitset::operator^(const my_bitset& other) const
{
	my_bitset res(dimension);

	for (size_t i = 0; i < buffer_size; ++i)
	{
		res.buffer[i] = buffer[i] ^ other.buffer[i];
	}

	return res;
}
