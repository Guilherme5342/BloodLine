#pragma once

#include "Spell.hpp"
#include "Bullet.hpp"
#include "GameObject.hpp"
#include "PlayerController.hpp"

class BloodBarrage : public Spell
{
private:
    GameObject &associated;

public:
    BloodBarrage(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController);
    void Activate() override; // Method to cast the spell
    // Other methods and properties as needed
};