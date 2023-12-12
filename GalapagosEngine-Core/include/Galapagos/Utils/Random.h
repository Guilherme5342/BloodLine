#pragma once

#include <random>

class Random
{
public:
	static float SlowFloat();
private:
	Random();
	Random& Random::GetInstance();
	static std::mt19937 m_engine;
	static std::uniform_int_distribution<std::mt19937::result_type> m_distribution;
};

