#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

class Spell : public Component
{
private:
    float damage;
    float range;

public:
    Spell(GameObject &associated, float damage, float range);
    virtual void Update(float dt) override;
    virtual void Render() override;
    virtual bool Is(std::string type) override;
};
