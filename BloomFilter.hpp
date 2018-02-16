/***************************************************************
<Austin Gladfeltere>
<BloomFilter.hpp>
<Program 4>
<
This file is the bloom filter implementation from Michael Schmatz blog.
add and possibly contains are the fucntions used in the analysis of the bloom filter.
The size and time complexity of these functions are O(1) amortized.>
***************************************************************/

#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H
 


#include "MurmurHash3.h"
#include <vector>
#include <array>



//the Bloom Filter data structure
struct BloomFilter {

	BloomFilter(uint64_t size, uint8_t numHashes);

	void add(const uint8_t *data, std::size_t len);
	bool possiblyContains(const uint8_t *data, std::size_t len) const;

	public:
		uint8_t m_numHashes;
		std::vector<bool> m_bits;


	};


//the constructor for the bloomfilter 
BloomFilter::BloomFilter(uint64_t size, uint8_t numHashes)
	: m_bits(size),
	m_numHashes(numHashes) {}


static std::array<uint64_t, 2> myhash(const uint8_t *data, std::size_t len)
{
	std::array<uint64_t, 2> hashValue;
	MurmurHash3_x64_128(data, len, 0, hashValue.data());
	return hashValue;
}

//array for hash functions
//called from MurmurHash3
inline uint64_t nthHash(uint8_t n,
	uint64_t hashA,
	uint64_t hashB,
	uint64_t filterSize) {
	return (hashA + n * hashB) % filterSize;
}

//add function
//puts a new element in the array
void BloomFilter::add(const uint8_t *data, std::size_t len) {
	auto hashValues = myhash(data, len);

	for (int n = 0; n < m_numHashes; n++)
	{
		m_bits[nthHash(n, hashValues[0], hashValues[1], m_bits.size())] = true;
	}
}

//boolean function for  false positives
bool BloomFilter::possiblyContains(const uint8_t *data, std::size_t len) const {
	auto hashValues = myhash(data, len);

	for (int n = 0; n < m_numHashes; n++)
	{
		if (!m_bits[nthHash(n, hashValues[0], hashValues[1], m_bits.size())])
		{
			return false;
		}
	}

	return true;
}


#endif