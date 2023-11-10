#include "Spell.hpp"

Spell::Spell(GameObject &associated, float damage, float range) : Component(associated), damage(damage), range(range) {}

void Spell::Update(float dt)
{
    // Implementation of spell behavior
}

void Spell::Render()
{
    // Render spell effects if any
}

bool Spell::Is(std::string type)
{
    return type == "Spell";
}
