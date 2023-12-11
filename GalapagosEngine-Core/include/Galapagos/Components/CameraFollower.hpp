#pragma once
#include <string>

#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Core/Component.hpp"

class CameraFollower : public Component
{
public:
    CameraFollower(GameObject &associated);

    void Update(float deltaTime) override;
    void Render() const override;
    bool Is(std::string type) const override;
};