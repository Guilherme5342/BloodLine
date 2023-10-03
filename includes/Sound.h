#pragma once

#include "SDL_mixer.h"
#include "Component.h"

class Sound : public Component {

private:
	std::shared_ptr<Mix_Chunk> chunk;
	int channel;

public:
	Sound(GameObject& associated);
	Sound(GameObject& associated, std::string filePath);
	~Sound();

	void Play(int times = 1);
	void Stop();
	void Open(std::string filePath);

	inline bool IsOpen() {
		return chunk != nullptr;
	}

	inline bool IsPlaying() {
		return Mix_Playing(channel);
	}

	void Update(float dt){}
	void Render(){}

	inline bool Is(std::string type) {
		return type == "Sound";
	}

};