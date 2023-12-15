#pragma once

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"
//#include "PlayerController.hpp"

class PlayerController;

class Spell : public Component
{
private:
    int healthCost;
    float damage;
    float range;
    GameObject &associated;
    PlayerController &playerController;

public:
    Spell(GameObject &associated, float damage, float range, int healthCost, PlayerController &playerController);
    float GetHealthCost() const;
    bool canCast(PlayerController &player);

    virtual void Activate() = 0; // Pure virtual function for spell activation
    virtual void Update(float dt) override;
    virtual void Render() const override;
    virtual bool Is(std::string type) const override;
};
