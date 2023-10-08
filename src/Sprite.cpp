#include "Sprite.hpp"
#include "Game.hpp"
#include "Resources.hpp"

Sprite::Sprite(GameObject &associated) : Component(associated)
{
	texture = nullptr;
	currentFrame = 0;
}

Sprite::Sprite(GameObject &associated, std::string filePath, int frameCount, float frameTime) : Sprite(associated)
{
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	Open(filePath);
}

Sprite::~Sprite()
{
	std::cout << "Sprite de: " << associated.Name() << std::endl;
}

void Sprite::Open(std::string filePath)
{

	texture = Resources::GetImage(filePath);

	if (!texture)
	{
		std::cout << "Erro " << SDL_GetError() << std::endl;
		return;
	}

	int texQuery = SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);

	if (texQuery != 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	cout << "Abrindo Sprite: " << filePath << endl;
	cout << width << endl;
	cout << height << endl;

	frameWidth = width / frameCount;

	frameHeight = height / frameCount;

	SetClip(associated.box.x, associated.box.y, frameWidth, frameHeight);


	associated.box.w = frameWidth;
	associated.box.h = frameHeight;
}

void Sprite::Render(int x, int y, int w, int h)
{
	SDL_Rect dstrect = SDL_Rect{x, y, w, h};

	SDL_RenderCopyEx(Game::Instance().GetRenderer(), texture.get(),
					 &clipRect, &dstrect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

void Sprite::Render()
{
	Render(associated.box.x -Camera::GetCurrentCamPos().x,
		   associated.box.y  - Camera::GetCurrentCamPos().y, width * scale.x, height * scale.y);
}

void Sprite::Update(float dt)
{
	timeElapsed += dt;

	if (loop)
		return;

	if (timeElapsed > frameTime) {
		currentFrame++;
		SetFrame(currentFrame);
	}
}