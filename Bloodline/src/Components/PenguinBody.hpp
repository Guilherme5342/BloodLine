#pragma once
#include <cstdint>
#include <memory>

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Math/Vec2.hpp"

class PenguinBody : public Component
{
public:
    PenguinBody(GameObject &associated);
    ~PenguinBody();

    void Start() override;
    void Update(float deltaTime) override;
    void NotifyCollision(GameObject &other) override;
    void Render() const override;
    inline bool Is(std::string type) const override { return type == "PenguinBody"; }
    inline Vec2 GetPosition() const { return m_associated.m_box.GetCenter(); }

    static PenguinBody *m_player;

private:
    std::weak_ptr<GameObject> m_pcannon;
    Vec2 m_speed = {0, 0};
    float m_linearSpeed = 0;
    const float m_linearVelocity = 1.5;
    const float m_angularVelocity = 100;
    const float m_maxFowardSpeed = 250;
    const float m_maxBackwardSpeed = -150;
    const float m_friction = m_linearVelocity / 8;
    float m_angle = 0;
    std::int32_t m_hp = 100;
};