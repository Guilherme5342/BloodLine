#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <cstdint>

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Utils/Timer.hpp"

class StaticSprite : public Component
{
public:
    StaticSprite(GameObject& associated);
    StaticSprite(GameObject& associated, std::string filePath, float secondsToSelfDestruct = 0);
    ~StaticSprite() override;

    void Open(std::string filePath);

    void Update(float deltaTime) override;
    void Render() const override;
    void Render(float x, float y) const;
    inline bool Is(std::string type) const override { return type == "StaticSprite"; }

    std::int32_t GetWidth() const;
    std::int32_t GetHeight() const;
    inline bool IsOpen() const { return m_texture != nullptr; }
    Vec2 GetScale() const { return m_scale; }

    void SetScale(float x, float y);
    void SetScale(float x);
    void SetScale(Vec2 scale);
    inline void SetClip(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h) { m_clipRect = { x, y, w, h }; }
    inline void SetDist(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h) { m_distRect = { x, y, w, h }; }
private:
    SDL_Texture* m_texture;
    SDL_Rect m_clipRect;
    SDL_Rect m_distRect;
    std::int32_t m_totalWidth = 0;
    std::int32_t m_totalHeight = 0;
    Vec2 m_scale = { 1.f, 1.f };
    Timer m_selfDestructCount;
    float m_secondsToSelfDestruct = 0;
};

