#pragma once
#include <SDL2/SDL_mixer.h>
#include <cstdint>

#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Core/Component.hpp"

class Sound : public Component
{
public:
    Sound(GameObject &associated);
    Sound(GameObject &associated, std::string filePath);
    ~Sound() override;

    void Open(std::string filePath);

    void Play(std::int32_t times = 1);
    void Stop();
    bool IsOpen() const;

    void Update(float deltaTime) override;
    void Render() const override;
    bool Is(std::string type) const override;

private:
    Mix_Chunk *m_chunk;
    std::int32_t m_channel;
};