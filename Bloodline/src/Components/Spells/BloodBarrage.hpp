#pragma once

#include "Spell.hpp"
#include "Components/Bullet.hpp"
#include "Components/PlayerController.hpp"
#include "Galapagos/Core/GameObject.hpp"

class BloodBarrage : public Spell
{
private:
    GameObject &associated;

public:
    BloodBarrage(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController);
    void Activate() override; // Method to cast the spell
    // Other methods and properties as needed
};