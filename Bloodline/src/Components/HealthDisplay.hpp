// HealthDisplay.hpp
#pragma once

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Components/Text.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Components/PlayerController.hpp"

class HealthDisplay : public Component {
private:
    Text text;
    PlayerController& pc;

public:
    HealthDisplay(GameObject& associated, int health, PlayerController& pc);

    void Update(float dt);
    void Render() const;
    bool Is(std::string type) const;
};
