#pragma once
#include <cstdint>

#include "Galapagos/Core/Component.h"
#include "Galapagos/Core/GameObject.h"
#include "Galapagos/Math/Vec2.h"
#include "Galapagos/Math/Rect.h"

class Collider : public Component
{
public:
    Collider(GameObject &associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});

    Rect m_box;
    void Update(float deltaTime) override;
    void Render() const override;
    inline bool Is(std::string type) const override { return type == "Collider"; }
    inline void SetScale(Vec2 scale) { m_scale = scale; }
    inline void SetOffset(Vec2 offset) { m_offset = offset; }

private:
    Vec2 m_scale = {1, 1};
    Vec2 m_offset = {0, 0};
};