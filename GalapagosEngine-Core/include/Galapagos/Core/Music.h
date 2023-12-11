#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>

class Music
{
public:
    Music();
    Music(std::string filePath);
    ~Music();

    void Open(std::string filePath);

    void Play(std::int32_t times);
    void Stop(std::int32_t msToStop);
    bool IsOpen() const;

private:
    Mix_Music *m_music;
};