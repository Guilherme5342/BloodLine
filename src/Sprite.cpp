#include "Sprite.hpp"
#include "Game.hpp"
#include "Resources.hpp"

Sprite::Sprite(GameObject &associated) : Component(associated)
{
	texture = nullptr;
	frameWidth = frameHeight = frameSpeed = frameCount = 0;
	frameStart = frameSpan = 0;
	currentFrame = frameStart;
}

Sprite::Sprite(GameObject &associated, std::string filePath, int columnCount, int rowCount, float frameTime) : Sprite(associated)
{
	this->animColumnCount = columnCount;
	this->animRowCount = rowCount;
	this->frameTime = frameTime;
	Open(filePath, columnCount, rowCount);
}

Sprite::~Sprite()
{
	std::cout << "Sprite de: " << associated.Name() << "Apagada" << std::endl;
}

void Sprite::Open(std::string filePath, int colunmCount, int rowCount)
{
	std::shared_ptr<SDL_Texture> oldTex;
	if (IsOpen()) {
		oldTex = texture;
	}

	texture = Resources::GetImage(filePath);
	
	if (texture == oldTex) {
		//cout << "Textura ja em uso " << filePath << endl;
		return;
	}

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

	//cout << "Abrindo Sprite: " << filePath << endl;
	//cout << width << endl;
	//cout << height << endl;
	this->animColumnCount = colunmCount;
	this->animRowCount = rowCount;
	
	frameCount = colunmCount * rowCount;

	frameWidth = width / colunmCount;

	frameHeight = height / rowCount;

	frameSpan = frameCount; // inicializa frameSpan (FrameFinal - FrameInical)

	//cout << "Frame Width: " << frameWidth << endl;
	//cout << "Frame Height: " << frameHeight << endl;

	SetFrame(0);

	associated.box.w = frameWidth;
	associated.box.h = frameHeight;
}

void Sprite::Render(int x, int y, int w, int h)
{
	SDL_Rect dstrect = SDL_Rect{x, y, w, h};

	SDL_RenderCopyEx(Game::Instance().GetRenderer(), texture.get(),
					 &clipRect, &dstrect, associated.angleDeg, nullptr, flipRenderer);
}

void Sprite::Render()
{
	Rect box;
	box = associated.box;

	Render(static_cast<int>(box.x -Camera::GetCurrentCamPos().x),
		   static_cast<int>(box.y  - Camera::GetCurrentCamPos().y), static_cast<int>(frameWidth * scale.x), static_cast<int>(frameHeight * scale.y));
}

void Sprite::Update(float dt)
{
	if (animColumnCount <= 1 && animRowCount <= 1)
		return;

	timeElapsed += dt;

	if (timeElapsed > frameTime) {
		currentFrame++;
		// Checa se o frame atual esta no Ultimo frame da Sprite Sheet
		// Caso esteja Loopando, ele repete, caso o contrário ele para no último
		if (currentFrame >= frameStart + frameSpan && loop) {
			currentFrame = frameStart;

		}
		else if(currentFrame >= frameStart + frameSpan && !loop)
		{
			currentFrame = frameStart + frameSpan - 1;
		}
		SetFrame(currentFrame);
		timeElapsed -= frameTime;
	}
}