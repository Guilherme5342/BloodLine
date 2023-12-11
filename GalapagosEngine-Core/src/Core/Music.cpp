#include "Galapagos/Core/Music.h"
#include <iostream>

#include "Galapagos/Core/Resources.h"

Music::Music()
{
    m_music = nullptr;
}

Music::Music(std::string filePath)
{
    m_music = nullptr;
    Open(filePath);
}

Music::~Music()
{
}

void Music::Open(std::string filePath)
{
    m_music = Resources::GetMusic(filePath);
}

void Music::Play(std::int32_t times)
{
    if (m_music == nullptr)
    {
        std::cerr << "Música não carregada!\n";
        return;
    }
    Mix_PlayMusic(m_music, times);
}
void Music::Stop(std::int32_t msToStop)
{
    Mix_FadeOutMusic(msToStop);
}

bool Music::IsOpen() const
{
    return m_music != nullptr;
}
