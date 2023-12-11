#pragma once
#include <cstdint>

#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Core/Component.hpp"

class Bullet : public Component
{
public:
    Bullet(GameObject &associated, float angle, float maxDistance, bool targetsPlayer, std::string sprite, std::uint32_t frameCount = 1, float frameTime = 1, bool loop = true);
    ~Bullet() override;

    void Update(float deltaTime) override;
    void NotifyCollision(GameObject& other) override;
    void Render() const override;
    inline bool Is(std::string type) const override { return type == "Bullet"; }

    std::int32_t GetDamage() const;

    bool m_targetsPlayer;
private:
    Vec2 m_speed;
    float m_distanceLeft;
    std::int32_t m_damage;
};