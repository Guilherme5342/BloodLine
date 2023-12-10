#pragma once
#include <cstdint>
#include <SDL2/SDL_ttf.h>

#include "Entity/Component.h"
#include "Entity/GameObject.h"
#include "math/Vec2.h"

class Text : public Component
{
public:
    enum class Style : std::uint8_t
    {
        SOLID = 0,
        SHADED,
        BLENDED
    };

    Text(GameObject &associated, std::string fontFile, std::int32_t fontSize, Style style, std::string text, SDL_Color color);
    ~Text();

    void Update(float deltaTime) override;
    void Render() const override;
    inline bool Is(std::string type) const override { return type == "Text"; }

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(Style style);
    void SetFontFile(std::string filePath);
    void SetFontSize(std::int32_t fontSize);

private:
    void RemakeTexture();

    TTF_Font *m_font;
    SDL_Texture *m_texture;

    std::string m_text;
    Style m_style;
    std::string m_fontFile;
    std::int32_t m_fontSize;
    SDL_Color m_color;
};