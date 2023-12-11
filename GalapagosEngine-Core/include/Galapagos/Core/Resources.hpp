#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

class Resources
{
public:
    static SDL_Texture *GetImage(std::string file);
    static void ClearImages();

    static Mix_Music *GetMusic(std::string file);
    static void ClearMusics();

    static Mix_Chunk *GetSound(std::string file);
    static void ClearSounds();

    static TTF_Font *GetFont(std::string file, std::int32_t size);
    static void ClearFonts();

private:
    static std::unordered_map<std::string, SDL_Texture *> m_imageTable;
    static std::unordered_map<std::string, Mix_Music *> m_musicTable;
    static std::unordered_map<std::string, Mix_Chunk *> m_soundTable;
    static std::unordered_map<std::string, TTF_Font *> m_fontTable;
};