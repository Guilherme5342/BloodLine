#include "Galapagos/Components/Text.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Components/PlayerController.hpp"
#include "Components/HealthDisplay.hpp"
#include "Galapagos/Core/Game.hpp"

#ifdef _WIN32
#define FONT "assets/font/Call me maybe.ttf"
#else
#define FONT "../assets/font/Call me maybe.ttf"
#endif

HealthDisplay::HealthDisplay(GameObject& associated, int health, PlayerController& pc)
    : Component(associated),
      text(associated,60, Text::Style::BLENDED, "Health: " + std::to_string(health), SDL_Color{255, 0, 0, 255}, FONT),
      pc(pc) {
    }

void HealthDisplay::Update(float dt) {
        text.SetText("Health: " + std::to_string(pc.GetHealth()));
    }

void HealthDisplay::Render() const {
        m_associated.m_box.SetCenter(Vec2(250, 50));
        text.RenderStatic(); 
}

bool HealthDisplay::Is(std::string type) const {
        return type == "HealthDisplay"; 
}

