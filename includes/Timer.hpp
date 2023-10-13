#pragma once


struct Timer {

private:
	float time;

public:
	Timer();
	void Update(float dt);

	inline float Get() {
		return time;
	}
};