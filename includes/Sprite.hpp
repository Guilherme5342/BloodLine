#pragma once

#ifdef _WIN32
#include "SDL_image.h"
#else
#include <SDL2/SDL_image.h>
#endif

#include "Component.hpp"
#include "Vector3.hpp"
#include "GameObject.hpp"


class Sprite : public Component
{

private:
	std::shared_ptr<SDL_Texture> texture;
	SDL_Rect clipRect;

	int width, height;
	int frameWidth, frameHeight;

	int currentFrame, frameCount;

	int frameSpeed;
	float timeElapsed, frameTime;

	bool loop;

	Vector2 scale = { 1,1 };

public:
	Sprite(GameObject &associated);
	Sprite(GameObject &associated, std::string filePath, int frameCount = 1, float frameTime = 1);
	~Sprite();

	void Open(std::string filePath);

	inline bool IsOpen()
	{
		return texture != nullptr;
	}

	inline void SetClip(int x, int y, int w, int h)
	{
		clipRect = SDL_Rect{x, y, w, h};
	}

	void Render(int x, int y, int w, int h);

	void Update(float dt);
	void Render();

	inline bool Is(std::string type)
	{
		return type == "Sprite";
	}

	inline int GetWidth()
	{
		return frameWidth * scale.x;
	}

	inline int GetHeight()
	{
		return frameHeight * scale.y;
	}

	inline void SetFrame(int frameIndex)
	{
		currentFrame = frameIndex % frameCount;
		//Atualiza o Source da SDL_Rect
		clipRect.x = currentFrame * frameWidth;
		clipRect.y = currentFrame * frameHeight;
	}

	inline void SetFrameCount(int frameCount) {
		this->frameCount = frameCount;
		this->frameWidth = width / frameCount;
		SetFrame(0);

		clipRect.w = frameWidth;

		associated.box.w = GetWidth();
	}

	inline void SetFrameTime(float frameTime) {
		this->frameTime = frameTime;
	}
};