#include "Text.hpp"
#include "Game.hpp"
#include "GameObject.hpp"

Text::Text(GameObject &associated, std::string filePath, int fontSize, TextStyle style, std::string text, SDL_Color color)
	: Component(associated)
{

	texture = nullptr;
	this->text = text;
	this->fontFile = filePath;
	this->fontSize = fontSize;
	this->style = style;
	this->color = color;

	font = Resources::GetFont(filePath, fontSize);

	if (!font)
	{
		cout << SDL_GetError() << endl;
	}

	RedrawTexture();
}

Text::~Text()
{
}

void Text::RedrawTexture()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}

	font = Resources::GetFont(fontFile, fontSize);

	if (!font)
	{
		cout << SDL_GetError() << endl;
	}

	SDL_Surface *surface{};
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

	texture = SDL_CreateTextureFromSurface(Game::GetRenderer(), surface);

	associated.box.w = surface->w;
	associated.box.h = surface->h;

	SDL_FreeSurface(surface);
}
void Text::Update(float dt)
{
}

void Text::Render()
{

	SDL_Rect srcRect{0, 0, static_cast<int>(associated.box.w), static_cast<int>(associated.box.h)};

	SDL_Rect dstRect{
		static_cast<int>(associated.box.x - Camera::GetCurrentCamPos().x),
		static_cast<int>(associated.box.y - Camera::GetCurrentCamPos().y),
		static_cast<int>(associated.box.w),
		static_cast<int>(associated.box.h)};

	SDL_RenderCopyEx(Game::GetRenderer(), texture, &srcRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

void Text::RenderStatic()
{

	SDL_Rect srcRect{0, 0, static_cast<int>(associated.box.w), static_cast<int>(associated.box.h)};

	SDL_Rect dstRect{
		static_cast<int>(associated.box.x ),
		static_cast<int>(associated.box.y ),
		static_cast<int>(associated.box.w),
		static_cast<int>(associated.box.h)};

	SDL_RenderCopyEx(Game::GetRenderer(), texture, &srcRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}
