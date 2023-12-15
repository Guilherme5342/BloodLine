// HealthDisplay.hpp
#pragma once

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Components/Text.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Components/PlayerController.hpp"

class HealthDisplay : public Component
{
public:
    HealthDisplay(GameObject &associated, int health, PlayerController &pc);

    void Update(float dt);
    void Render() const;
    inline bool Is(std::string type) const { return type == "HealthDisplay"; }

private:
    Text m_text;
    PlayerController &m_pc;
};
