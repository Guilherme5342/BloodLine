#pragma once
#include <cstdint>
#include <memory>

#include "Galapagos/Core/Component.h"
#include "Galapagos/Core/GameObject.h"
#include "Galapagos/Utils/Timer.h"

class PenguinCannon : public Component
{
public:
    PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody);

    void Start() override;
    void Update(float deltaTime) override;
    void NotifyCollision(GameObject &other) override;
    void Render() const override;
    inline bool Is(std::string type) const override { return type == "PenguinCannon"; }

    void Shoot();

private:
    std::weak_ptr<GameObject> m_pbody;
    float m_angle = 0;

    Timer m_timer;
};