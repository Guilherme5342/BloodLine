#pragma once

#include "Spell.hpp"
#include "Bullet.hpp"
#include "GameObject.hpp"
#include "PlayerController.hpp"

class BloodSpell : public Spell
{
private:
    // BloodSpell-specific properties (e.g., cost, cooldown)

public:
    BloodSpell(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController);
    void Activate() override; // Method to cast the spell
    // Other methods and properties as needed
};
