#pragma once

#include "SDL_image.h"
#include "Component.h"


class Sprite : public Component{

private:
	std::shared_ptr<SDL_Texture> texture;
	SDL_Rect clipRect;

	int width, height;

	int frame, frameCount, frameWidth;

	float timeElapsed;



public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, std::string filePath);
	~Sprite();

	void Open(std::string filePath);

	inline bool IsOpen() {
		return texture != nullptr;
	}

	inline void SetClip(int x, int y, int w, int h) {
		clipRect = SDL_Rect{ x,y,w,h };
	}

	void Render(int x, int y);
	void Update(float dt);
	void Render();

	inline bool Is(std::string type) {
		return type == "Sprite";
	}

	inline int GetWidth() {
		return width;
	}

	inline int GetHeight() {
		return height;
	}

	inline void SetFrame(int frameIndex) {
		frame = frameIndex % frameCount;

	}
	
};