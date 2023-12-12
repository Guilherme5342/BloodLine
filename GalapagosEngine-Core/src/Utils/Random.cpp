#include "Galapagos/Utils/Random.h"

std::mt19937 Random::m_engine;
std::uniform_int_distribution<std::mt19937::result_type> Random::m_distribution;

float Random::SlowFloat()
{
	return static_cast<float>(m_distribution(m_engine)) / static_cast<float>(std::numeric_limits<std::uint32_t>::max());
}

Random::Random()
{
	m_engine.seed(std::random_device()());
}

Random& Random::GetInstance()
{
	static Random instance;
	return instance;
}