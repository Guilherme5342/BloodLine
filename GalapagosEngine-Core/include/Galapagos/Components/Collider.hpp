#pragma once
#include <cstdint>

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Math/Vec2.hpp"
#include "Galapagos/Math/Rect.hpp"

class Collider : public Component
{
public:
    Collider(GameObject &associated, bool fixed = false, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});

    Rect m_box;
    bool isTrigger;

    void FixedUpdate(float fixedDeltaime) override;
    void Update(float deltaTime) override;
    void Render() const override;
    inline bool Is(std::string type) const override { return type == "Collider"; }
    inline void SetScale(Vec2 scale) { m_scale = scale; }
    inline void SetOffset(Vec2 offset) { m_offset = offset; }
    inline bool GetFixed() const { return m_fixed; }

private:
    Vec2 m_scale = {1, 1};
    Vec2 m_offset = {0, 0};
    bool m_fixed;
    
};