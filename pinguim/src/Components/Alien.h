#pragma once
#include <string>
#include <cstdint>
#include <queue>
#include <vector>
#include <memory>

#include "Entity/Component.h"
#include "math/Vec2.h"
#include "Timer.h"

class Alien : public Component
{
public:
    Alien(GameObject &associated, std::int32_t minionCount);
    ~Alien() override;

    void Start() override;
    void Update(float deltaTime) override;
    void NotifyCollision(GameObject &other) override;
    void Render() const override;
    inline bool Is(std::string type) const override { return type == "Alien"; }

    static std::int32_t m_alienCount;
private:

    void Shoot(Vec2 playerPos) const;

    enum class AlienState {
        MOVING = 0,
        RESTING
    };

    AlienState m_state = AlienState::RESTING;
    Timer m_restTime;
    float m_waitTime;
    Vec2 m_destination;
    Vec2 m_speed;
    std::int32_t m_hp;
    std::uint32_t m_minionCount;
    std::vector<std::weak_ptr<GameObject>> m_minionArray;
};