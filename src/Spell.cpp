#include "Spell.hpp"
#include "PlayerController.hpp"

Spell::Spell(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController)
    : Component(associated), damage(damage), range(range), associated(associated), healthCost(healthCost), playerController(playerController) {}

void Spell::Update(float dt)
{
    // Update logic for the spell. This might be empty for some spells.
}

void Spell::Render()
{
    // Render logic for the spell. This might involve rendering spell effects or animations.
}

bool Spell::Is(std::string type)
{
    return type == "Spell";
}

float Spell::GetHealthCost() const
{
    return healthCost;
}

bool Spell::canCast(PlayerController &player)
{
    if (player.GetHealth() >= healthCost)
        return true;
    else
        return false;
}