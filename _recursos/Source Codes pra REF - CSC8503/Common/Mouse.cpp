#include "Mouse.h"
#include <string>

using namespace NCL;

Mouse::Mouse() {
	memset(buttons		, 0, sizeof(bool)  * MOUSE_MAX);
	memset(holdButtons	, 0, sizeof(bool)  * MOUSE_MAX);
	memset(doubleClicks	, 0, sizeof(bool)  * MOUSE_MAX);
	memset(lastClickTime, 0, sizeof(float) * MOUSE_MAX);

	lastWheel	= 0;
	frameWheel	= 0;
	sensitivity = 7.0f;	//Chosen for no other reason than it's a nice value for my Deathadder ;)
	clickLimit	= 200.0f;
}

void Mouse::UpdateFrameState(float msec) {
	memcpy(holdButtons, buttons, sizeof(bool)  * MOUSE_MAX);

	//We sneak this in here, too. Resets how much the mouse has moved since last update
	relativePosition.ToZero();
	//And the same for the mouse wheel
	frameWheel = 0;

	for (int i = 0; i < MOUSE_MAX; ++i) {
		if (lastClickTime[i] > 0) {
			lastClickTime[i] -= msec;
			if (lastClickTime[i] <= 0.0f) {
				doubleClicks[i] = false;
				lastClickTime[i] = 0.0f;
			}
		}
	}
}

void	Mouse::Sleep() {
	isAwake = false; 
	memset(buttons		, 0, sizeof(bool)  * MOUSE_MAX);
	memset(holdButtons	, 0, sizeof(bool)  * MOUSE_MAX);
	memset(doubleClicks	, 0, sizeof(bool)  * MOUSE_MAX);
	memset(lastClickTime, 0, sizeof(float) * MOUSE_MAX);
	lastWheel  = 0;
	frameWheel = 0;
}

void	Mouse::Wake() {
	isAwake = true; 
}

void	Mouse::SetAbsolutePosition(const Vector2& pos) {
	absolutePosition = pos;
}

void	Mouse::SetAbsolutePositionBounds(const Vector2& bounds) {
	absolutePositionBounds = bounds;
}