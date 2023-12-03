// HealthDisplay.hpp
#pragma once

#include "Component.hpp"
#include "Text.hpp"
#include "GameObject.hpp"
#include "PlayerController.hpp"

class HealthDisplay : public Component {
private:
    Text text;
    PlayerController& pc;

public:
    HealthDisplay(GameObject& associated, int health, PlayerController& pc);

    void Update(float dt);
    void Render();
    bool Is(string type);
};
