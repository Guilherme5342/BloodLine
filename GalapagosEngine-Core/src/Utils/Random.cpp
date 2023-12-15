#include "Galapagos/Utils/Random.h"

std::uint64_t Random::Long()
{
	static std::uint64_t x = std::random_device()();
	std::uint64_t z = (x += UINT64_C(0x9E3779B97F4A7C15));
	z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
	z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
	return z ^ (z >> 31);
}

double Random::Double()
{
	static std::uint64_t x = std::random_device()();
	std::uint64_t z = (x += UINT64_C(0x9E3779B97F4A7C15));
	z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
	z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
	return static_cast<double>(z ^ (z >> 31)) / static_cast<double>(std::numeric_limits<std::uint64_t>::max());
}