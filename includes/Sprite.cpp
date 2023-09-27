#include "Sprite.h"
#include "Game.h"
#include "Resources.h"


Sprite::Sprite(GameObject& associated) : Component(associated)
{
	texture = nullptr;
}

Sprite::Sprite(GameObject& associated,std::string filePath) : Sprite(associated) {
	Open(filePath);
}

Sprite::~Sprite()
{
	if (IsOpen()) {
		SDL_DestroyTexture(texture.get());
		std::cout << "Sprite de: " << associated.Name() << std::endl;
	}
}

void Sprite::Open(std::string filePath) {

	texture = Resources::GetImage(filePath);

	if (!texture) {
		std::cout << "Erro " << SDL_GetError() << std::endl;
		return;
	}

	int texQuery = SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
	
	if (texQuery != 0) {
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	cout << "Abrindo Sprite: " << texture << endl;

	SetClip(associated.box.x, associated.box.y, width, height);

	associated.box.w = width;
	associated.box.h = height;
}

void Sprite::Render(int x, int y, int w, int h) {
	
	SDL_Rect dstrect = SDL_Rect{ x,y,w,h };

	SDL_RenderCopyEx(Game::Instance().GetRenderer(), texture.get(),
		&clipRect, &dstrect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

void Sprite::Render() {
	
	Render(associated.box.x - Camera::GetCurrentCamPos().x, 
		associated.box.y - Camera::GetCurrentCamPos().y, width, height);
}

void Sprite::Update(float dt) {
	timeElapsed += dt;
}