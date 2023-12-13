#pragma once
#include <cstdint>
#include <vector>

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Utils/Timer.hpp"
#include "Galapagos/Utils/Particle.hpp"

struct SDL_Texture;

struct ParticleConfig
{
    Vec2 position;
    Vec2 velocity;
    Vec2 velocityVariation;
    SDL_Color startColor;
    SDL_Color endColor;
    float startSize = 1.0f;
    float endSize = 1.0f;
    float sizeVariation = 0.0f;
    float lifeTime = 1.0f;
    float rate = 0.5f;
};

class ParticleEmmiter : public Component
{
public:
    enum class Type {
        Rect = 0,
        Texture,
        Circle
    };

    ParticleEmmiter(GameObject& associated, std::uint32_t numberOfParticles, Type type = Type::Rect, std::string textureFile = "");
    void Start() override;
    void Update(float deltaTime) override;
    void Render() const override;
    inline bool Is(std::string type) const override { return type == "ParticleEmmiter"; }

    void SetNumberOfParticles(std::uint32_t numberOfParticles);
    void Emit(const ParticleConfig& particleConfig);
    inline void ToggleEmitter(bool emit) { m_emit = emit; }
private:
    struct Particle
    {
        Vec2 position = { 0.0f, 0.0f };
        Vec2 velocity = { 0.0f, 0.0f };
        float rotation = 0.0f;
        SDL_Color startColor = { 255, 255, 255, 255 };
        SDL_Color endColor = { 255, 255, 255, 255 };
        float startSize = 1.0f;
        float endSize = 0.0f;
        float lifeTime = 1.0f;
        float lifeRemaning = 0.0f;
        bool active = false;
    };

    Timer m_timer;
    bool m_emit = true;

    SDL_Texture* m_texture = nullptr;
    Type m_type = Type::Rect;
    SDL_Rect m_textureClipRect = { 0, 0, 0, 0 };


    std::vector<Particle> m_particleList;
    std::uint32_t m_currentParticle;
};

