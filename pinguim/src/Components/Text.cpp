#include "Text.h"

#include "Game.h"
#include "Camera.h"
#include "Resources.h"

Text::Text(GameObject &associated, std::string fontFile, std::int32_t fontSize, Style style, std::string text, SDL_Color color)
    : Component(associated)
{
    m_font = nullptr;
    m_texture = nullptr;
    m_text = text;
    m_style = style;
    m_fontFile = fontFile;
    m_fontSize = fontSize;
    m_color = color;
    RemakeTexture();
}

Text::~Text()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
}

void Text::Update(float deltaTime)
{
    /*     static std::int32_t counter = 0;
        counter++;
        float offset = (counter < 800) * 0.0001 + (counter >= 800) * -0.0001;
        m_associated.m_box.Scale(1 + offset, 1 + offset);

        counter = (counter < 1600) * counter; */
}

void Text::Render() const
{
    if (m_font && m_texture)
    {
        SDL_Rect clipRect = SDL_Rect{0, 0, static_cast<std::int32_t>(m_associated.m_box.w), static_cast<std::int32_t>(m_associated.m_box.h)};
        SDL_Rect distRect = SDL_Rect{static_cast<std::int32_t>(m_associated.m_box.x - Camera::position.x),
                                     static_cast<std::int32_t>(m_associated.m_box.y - Camera::position.y),
                                     static_cast<std::int32_t>(clipRect.w),
                                     static_cast<std::int32_t>(clipRect.h)};
        SDL_RenderCopyEx(Game::GetRenderer(), m_texture, &clipRect, &distRect, m_associated.m_angleDeg, nullptr, SDL_FLIP_NONE);
    }
    else {
        std::cout << "no render\n";
    }
    
}

void Text::SetText(std::string text)
{
    m_text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color)
{
    m_color = color;
    RemakeTexture();
}

void Text::SetStyle(Style style)
{
    m_style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string filePath)
{
    m_fontFile = filePath;
    RemakeTexture();
}

void Text::SetFontSize(std::int32_t fontSize)
{
    m_fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
    m_font = Resources::GetFont(m_fontFile, m_fontSize);

    if (!m_font)
    {
        return;
    }

    SDL_Surface *renderedText = nullptr;
    switch (m_style)
    {
    case Text::Style::SOLID:
        renderedText = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);
        break;
    case Text::Style::SHADED:
        renderedText = TTF_RenderText_Shaded(m_font, m_text.c_str(), m_color, {0, 0, 0, 255});
        break;
    case Text::Style::BLENDED:
        renderedText = TTF_RenderText_Blended(m_font, m_text.c_str(), m_color);
        break;
    }

    if (!renderedText)
    {
        return;
    }

    m_associated.m_box.w = renderedText->w;
    m_associated.m_box.h = renderedText->h;

    m_texture = SDL_CreateTextureFromSurface(Game::GetRenderer(), renderedText);
    SDL_FreeSurface(renderedText);
}
