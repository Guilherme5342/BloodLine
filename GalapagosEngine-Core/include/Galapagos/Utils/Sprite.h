#pragma once
#include <SDL2/SDL.h>
#include <cstdint>  

struct Sprite
{
    SDL_Texture* m_texture;
    std::int32_t m_totalWidth = 0;
    std::int32_t m_totalHeight = 0;
};

