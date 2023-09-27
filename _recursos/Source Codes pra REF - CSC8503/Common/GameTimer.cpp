#include "GameTimer.h"

using namespace NCL;

GameTimer::GameTimer(void)	{
	firstPoint = std::chrono::high_resolution_clock::now();
	nowPoint   = firstPoint;
	Tick();
}

double GameTimer::GetTotalTime() const {
	Timepoint time = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> diff;
	diff = std::chrono::duration_cast<std::chrono::microseconds>(time - firstPoint);

	return diff.count();// / 1000.0f;
}

/*
Casting to milliseconds directly gives us integers, which will be often 0 for
programs that don't do very much...
*/
void	GameTimer::Tick() {
	Timepoint latestTime = std::chrono::high_resolution_clock::now();

	auto msec = std::chrono::duration_cast<std::chrono::microseconds>(latestTime - nowPoint);
	
	nowPoint = latestTime;

	timeDelta = msec.count() / 1000.0f;
}