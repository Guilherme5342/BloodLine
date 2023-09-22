#include "Text.h"
#include "Game.h"
#include "GameObject.h"


Text::Text(GameObject& associated, std::string filePath, int fontSize, TextStyle style, std::string text, SDL_Color color) 
: Component(associated) {

	texture = nullptr;
	this->text = text;
	this->fontFile = filePath;
	this->fontSize = fontSize;
	this->style = style;
	this->color = color;

}


Text::~Text() {

}

void Text::RedrawTexture() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}

	SDL_Surface* surface{};
	switch (style)
	{
		case SOLID:
			surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
			break;
		case SHADED:
			surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, color);
			break;
		case BLENDED:
			surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
			break;	
	}

	texture = SDL_CreateTextureFromSurface(Game::Instance().GetRenderer(), surface);

	associated.box.w = surface->w;
	associated.box.h = surface->h;

	SDL_FreeSurface(surface);
}
void Text::Update(float dt) {

}

void Text::Render() {


	SDL_Rect srcRect {associated.box.x,associated.box.y, associated.box.w,associated.box.h}, 
		dstRect{associated.box.x - Camera::GetCurrentCamPos().x, associated.box.y - Camera::GetCurrentCamPos().y ,
	associated.box.w,associated.box.h };

	SDL_RenderCopyEx(Game::Instance().GetRenderer(), texture, &srcRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

