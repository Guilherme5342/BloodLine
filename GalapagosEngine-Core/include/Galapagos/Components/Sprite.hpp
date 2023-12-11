#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <cstdint>

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Utils/Timer.hpp"

class Sprite : public Component
{
public:
    Sprite(GameObject &associated);
    Sprite(GameObject &associated, std::string filePath, std::uint32_t frameCount = 1, float frameTime = 1, bool loop = true, float secondsToSelfDestruct = 0);
    ~Sprite() override;

    void Open(std::string filePath, std::uint32_t frameCount = 1, float frameTime = 1);

    void Update(float deltaTime) override;
    void Render() const override;
    void Render(float x, float y) const;
    bool Is(std::string type) const override;

    std::int32_t GetWidth() const;
    std::int32_t GetHeight() const;
    bool IsOpen() const;
    Vec2 GetScale() const;

    void SetScale(float x, float y);
    void SetScale(float x);
    void SetScale(Vec2 scale);
    void SetClip(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h);
    void SetFrame(std::uint32_t frame);
    void SetFrameCount(std::uint32_t frameCount);
    void SetFrameTime(float frameTime);

private:
    SDL_Texture *m_texture;
    SDL_Rect m_clipRect;
    std::int32_t m_width;
    std::int32_t m_height;
    std::uint32_t m_frameCount = 1;
    std::uint32_t m_currentFrame = 1;
    float m_timeElapsed = 0;
    float m_frameTime = 1;
    Vec2 m_scale = {1.f, 1.f};
    bool m_loop = true;
    Timer m_selfDestructCount;
    float m_secondsToSelfDestruct = 0;
};