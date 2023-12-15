#pragma once

#include "Components/Spells/Spell.hpp"
#include "Components/Bullet.hpp"
#include "Components/PlayerController.hpp"
#include "Galapagos/Core/GameObject.hpp"

class BloodSpell : public Spell
{
private:
    GameObject &associated;

public:
    BloodSpell(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController);
    void Activate() override; // Method to cast the spell
    // Other methods and properties as needed
};
