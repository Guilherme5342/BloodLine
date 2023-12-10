#include "Resources.h"

#include <SDL2/SDL_image.h>
#include <iostream>

#include "Game.h"

std::unordered_map<std::string, SDL_Texture *> Resources::m_imageTable;
std::unordered_map<std::string, Mix_Music *> Resources::m_musicTable;
std::unordered_map<std::string, Mix_Chunk *> Resources::m_soundTable;
std::unordered_map<std::string, TTF_Font *> Resources::m_fontTable;

SDL_Texture *Resources::GetImage(std::string file)
{
    if (m_imageTable.find(file) == m_imageTable.end())
    {
        SDL_Texture *texture = IMG_LoadTexture(Game::GetRenderer(), file.c_str());
        if (!texture)
        {
            std::cerr << "Erro ao carregar imagem! [" << file << "]. " << SDL_GetError() << "\n";
            exit(1);
        }
        m_imageTable.try_emplace(file, texture);
    }
    return m_imageTable.at(file);
}

void Resources::ClearImages()
{
    for (const auto &image : m_imageTable)
    {
        SDL_DestroyTexture(image.second);
    }
    m_imageTable.clear();
}

Mix_Music *Resources::GetMusic(std::string file)
{
    if (m_musicTable.find(file) == m_musicTable.end())
    {
        Mix_Music *music = Mix_LoadMUS(file.c_str());
        if (music == nullptr)
        {
            std::cout << "Erro ao carregar música! [" << file << "]. " << SDL_GetError() << "\n";
            exit(1);
        }
        m_musicTable.try_emplace(file, music);
    }
    return m_musicTable.at(file);
}

void Resources::ClearMusics()
{
    for (const auto &music : m_musicTable)
    {
        Mix_FreeMusic(music.second);
    }
    m_musicTable.clear();
}

Mix_Chunk *Resources::GetSound(std::string file)
{
    if (m_soundTable.find(file) == m_soundTable.end())
    {
        Mix_Chunk *chunk = Mix_LoadWAV(file.c_str());
        if (chunk == nullptr)
        {
            std::cerr << "Erro ao carregar música! [" << file << "]. " << SDL_GetError() << "\n";
            exit(1);
        }
        m_soundTable.try_emplace(file, chunk);
    }
    return m_soundTable.at(file);
}

void Resources::ClearSounds()
{
    for (const auto &sound : m_soundTable)
    {
        Mix_FreeChunk(sound.second);
    }
    m_soundTable.clear();
}

TTF_Font *Resources::GetFont(std::string file, std::int32_t size)
{
    std::string key = std::to_string(size).append(file);
    
    if (m_fontTable.find(key) == m_fontTable.end())
    {
        TTF_Font *font = TTF_OpenFont(file.c_str(), size);
        if (font == nullptr)
        {
            std::cerr << "Erro ao carregar fonte! [" << file << "]["<< size <<"]. " << SDL_GetError() << "\n";
            exit(1);
        }
        m_fontTable.try_emplace(key, font);
    }
    return m_fontTable.at(key);
}

void Resources::ClearFonts()
{
    for (const auto &font : m_fontTable)
    {
        TTF_CloseFont(font.second);
    }
    m_fontTable.clear();
}