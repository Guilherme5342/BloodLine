#include "Timer.hpp"

Timer::Timer() {
	time = 0;
}

Timer::~Timer()
{
}

void Timer::Update(float dt) {

	time += dt;
}