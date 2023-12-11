#include "Galapagos/Components/Sound.hpp"

#include <iostream>
#include <SDL2/SDL_mixer.h>

#include "Galapagos/Core/Resources.hpp"

Sound::Sound(GameObject &associated) : Component(associated)
{
    m_chunk = nullptr;
}
Sound::Sound(GameObject &associated, std::string filePath) : Component(associated)
{
    Open(filePath);
}

Sound::~Sound()
{
    if (m_chunk != nullptr)
    {
        Mix_HaltChannel(m_channel);
    }
}

void Sound::Open(std::string filePath)
{
    m_chunk = Resources::GetSound(filePath);
}

void Sound::Play(std::int32_t times /*= 1*/)
{
    if (m_chunk == nullptr)
    {
        std::cerr << "Música não carregada!\n";
        return;
    }
    m_channel = Mix_PlayChannel(-1, m_chunk, times - 1);
}
void Sound::Stop()
{
    if (m_chunk != nullptr)
    {
        Mix_HaltChannel(m_channel);
    }
}

bool Sound::IsOpen() const
{
    return m_chunk != nullptr;
}

void Sound::Update(float deltaTime)
{
}

void Sound::Render() const
{
}

bool Sound::Is(std::string type) const
{
    return type == "Sound";
}
