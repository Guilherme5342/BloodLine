/******************************************************************************
Class:GameTimer
Author:Rich Davison
Description: The GameTimer class provides a simple mechanism to keep track of
how many milliseconds have elapsed every frame. Calls To the Tick function will
update the internals of the system, while GetTimeDelta returns how many
milliseconds have passed between calls to Tick. 

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <chrono>

namespace NCL {
	typedef  std::chrono::time_point<std::chrono::high_resolution_clock>  Timepoint;

	class GameTimer {
	public:
		GameTimer(void);
		~GameTimer(void) {}

		double	GetTotalTime() const;
		float	GetTimeDelta() const { return timeDelta; };
		void	Tick();
	protected:
		float		timeDelta;	//Last time GetTimedMS was called
		Timepoint	firstPoint;
		Timepoint	nowPoint;
	};
}

