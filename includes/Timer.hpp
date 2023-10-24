#pragma once


struct Timer {

private:
	float time;

public:
	Timer();
	~Timer();

	void Update(float dt);

	inline float Get() {
		return time;
	}

	inline void Reset() {
		time = 0;
	}
};