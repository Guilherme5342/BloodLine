#pragma once

#include "SDL_mixer.h"
#include <iostream>
#include <string.h>
#include <string>

class Music {
private:
	std::shared_ptr<Mix_Music> music;

public:
	Music();
	Music(std::string filePath);
	~Music();

	void Play(int times = -1);
	void Stop(int msToStop = 1500);

	void Open(std::string filePath);
	inline bool IsOpen() {
		return music != nullptr;
	}
};