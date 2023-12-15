#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <cstdint>

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Utils/Timer.hpp"

class AnimatedSprite : public Component
{
public:
    AnimatedSprite(GameObject &associated);
    AnimatedSprite(GameObject &associated, std::string filePath);
    AnimatedSprite(GameObject &associated, std::string filePath, std::uint32_t frameCount, float frameTime, bool loop = true);
    AnimatedSprite(GameObject &associated, std::string filePath, std::uint32_t frameCount, float frameTime, bool loop, std::uint32_t columnCount, std::uint32_t rowCount, float secondsToSelfDestruct = 0);
    ~AnimatedSprite() override;

    void Open(std::string filePath, std::uint32_t columnCount, std::uint32_t rowCount, float frameTime);

    void Update(float deltaTime) override;
    void Render() const override;
    void Render(float x, float y) const;
    inline bool Is(std::string type) const override{return type == "AnimatedSprite";}

    std::int32_t GetWidth() const;
    std::int32_t GetHeight() const;
    inline bool IsOpen() const { return m_texture != nullptr; }
    Vec2 GetScale() const;

    void SetScale(float x, float y);
    void SetScale(float x);
    void SetScale(Vec2 scale);
    inline void SetClip(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h) { m_clipRect = { x, y, w, h }; }
    inline void SetDist(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h) { m_distRect = { x, y, w, h }; }

private:
    SDL_Texture *m_texture;
    SDL_Rect m_clipRect;
    SDL_Rect m_distRect;
    std::int32_t m_totalWidth = 0;
    std::int32_t m_totalHeight = 0;
    std::int32_t m_frameWidth = 0;
    std::int32_t m_frameHeight = 0;
    std::uint32_t m_frameCount = 1;
    std::uint32_t m_columnCount = 1;
    std::uint32_t m_rowCount = 1;
    std::uint32_t m_currentFrame = 1;
    float m_timeElapsed = 0;
    float m_frameTime = 1;
    bool m_loop = true;
    Vec2 m_scale = {1.f, 1.f};
    Timer m_selfDestructCount;
    float m_secondsToSelfDestruct = 0;
};