#pragma once

#include "Component.h"
#include "SDL_ttf.h"

typedef enum FontStyle {
	DEFAULT = TTF_STYLE_NORMAL,
	BOLD = TTF_STYLE_BOLD,
	ITALIC = TTF_STYLE_ITALIC,
	UNDERLINE = TTF_STYLE_UNDERLINE
};

typedef enum TextStyle {
	SOLID,
	SHADED,
	BLENDED
};
class Text : public Component {

private:
	std::shared_ptr<TTF_Font> font;
	SDL_Texture* texture;

	std::string fontFile;
	std::string text;

	int fontSize;
	TextStyle style;

	SDL_Color color;

	void RedrawTexture();
	
	
public:
	Text(GameObject& associated,std::string filePath, int fontSize, TextStyle style, std::string text, SDL_Color color);
	~Text();

	void SetText(std::string text);
	void SetFontSize(int fontSize);

	inline void SetFontStyle(FontStyle fontStyle) {
		TTF_SetFontStyle(font.get(), fontStyle);
	}

	void Update(float dt);
	void Render();
	inline bool Is(std::string type) {
		return type == "Text";
	}

};