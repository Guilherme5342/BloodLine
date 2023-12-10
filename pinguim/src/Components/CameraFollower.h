#pragma once
#include <string>

#include "Entity/GameObject.h"
#include "Entity/Component.h"

class CameraFollower : public Component
{
public:
    CameraFollower(GameObject &associated);

    void Update(float deltaTime) override;
    void Render() const override;
    bool Is(std::string type) const override;
};