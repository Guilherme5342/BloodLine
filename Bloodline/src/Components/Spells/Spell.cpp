#include "Spell.hpp"
#include "Components/PlayerController.hpp"

Spell::Spell(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController)
    : Component(associated), m_damage(damage), m_range(range), m_associated(associated), m_healthCost(healthCost), m_playerController(playerController) {}

void Spell::Update(float dt)
{
    // Update logic for the spell. This might be empty for some spells.
}

void Spell::Render() const
{
    // Render logic for the spell. This might involve rendering spell effects or animations.
}

bool Spell::Is(std::string type) const
{
    return type == "Spell";
}

float Spell::GetHealthCost() const
{
    return m_healthCost;
}

bool Spell::canCast(PlayerController &player)
{
    if (player.GetHealth() >= m_healthCost)
        return true;
    else
        return false;
}