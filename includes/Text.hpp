#pragma once

#include "Component.hpp"

#ifdef _WIN32
#include "SDL_ttf.h"
#else
#include <SDL2/SDL_ttf.h>
#endif

typedef enum FontStyle
{
	DEFAULT = TTF_STYLE_NORMAL,
	BOLD = TTF_STYLE_BOLD,
	ITALIC = TTF_STYLE_ITALIC,
	UNDERLINE = TTF_STYLE_UNDERLINE
};

typedef enum TextStyle
{
	SOLID,
	SHADED,
	BLENDED
};
class Text : public Component
{

private:
	std::shared_ptr<TTF_Font> font;
	SDL_Texture *texture;

	std::string fontFile;
	std::string text;

	int fontSize;
	TextStyle style;

	SDL_Color color;

	void RedrawTexture();

public:
	Text(GameObject &associated, std::string filePath, int fontSize, TextStyle style, std::string text, SDL_Color color);
	~Text();

	inline void SetText(std::string text)
	{
		this->text = text;
		RedrawTexture();
	}
	inline void SetTextStyle(TextStyle style)
	{
		this->style = style;
		RedrawTexture();
	}
	inline void SetFontFile(std::string fontPath)
	{
		this->fontFile = fontPath;
		RedrawTexture();
	}
	inline void SetFontSize(int fontSize)
	{
		this->fontSize = fontSize;
		RedrawTexture();
	}
	inline void SetColor(SDL_Color color)
	{
		this->color = color;
		RedrawTexture();
	}

	inline void SetFontStyle(FontStyle fontStyle)
	{
		TTF_SetFontStyle(font.get(), fontStyle);
	}

	void Update(float dt);
	void Render();
	void RenderStatic();
	inline bool Is(std::string type)
	{
		return type == "Text";
	}
};