#pragma once

#ifdef _WIN32
#include "SDL_image.h"
#else
#include <SDL2/SDL_image.h>
#endif

#include "Component.hpp"
#include "Vector3.hpp"
#include "GameObject.hpp"

// Ideia: criar uma Struct que guarda os Dados relevantes da Sprite
struct SpriteData {
public:
	std::string filePath;
	int width, height;

};

class Sprite : public Component
{

private:
	std::shared_ptr<SDL_Texture> texture;

	SDL_Rect clipRect;

	SDL_RendererFlip flipRenderer;

	int width, height;
	int frameWidth, frameHeight;

	int currentFrame, frameCount, animColumnCount, animRowCount;

	int frameStart, frameSpan;

	int frameSpeed;

	float timeElapsed, frameTime;

	bool loop, flipX;

	Vector2 scale = { 1,1 };

public:
	Sprite(GameObject &associated);
	Sprite(GameObject &associated, std::string filePath, int columnCount = 1, int rowCount = 1, float frameTime = 1);
	~Sprite();

	void Open(std::string filePath, int colunmCount = 1, int rowCount = 1);

	inline bool IsOpen()
	{
		return texture != nullptr;
	}

	inline void SetClip(int x, int y, int w, int h)
	{
		clipRect = SDL_Rect{x, y, w, h};
	}

	inline void FlipX() {
		flipX = !flipX;

		flipRenderer = flipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
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
		int frameX = frameIndex % animColumnCount;
		int frameY = frameIndex / animColumnCount;
		
		SetClip(frameX * frameWidth,frameY * frameHeight, frameWidth, frameHeight);

	}

	inline void SetFrameCount(int frameCount) {
		this->frameCount = frameCount;
		
		currentFrame = frameStart;

		clipRect.x = currentFrame;
		clipRect.y = currentFrame;

		clipRect.w = frameWidth;
		clipRect.h = frameHeight;

		associated.box.w = GetWidth();
		associated.box.h = GetHeight();
	}

	inline void SetFrameTime(float frameTime) {
		this->frameTime = frameTime;
	}
	
	inline void SetFrameStart(float frameStart) {
		this->frameStart = frameStart;
		currentFrame = frameStart;
	}
	inline void SetFrameSpan(int frameStart, int frameEnd) {
		this->frameStart = frameStart;
		frameSpan = frameEnd - frameStart;
		currentFrame = frameStart;
	}
};