#include "Text.hpp"
#include "GameObject.hpp"
#include "PlayerController.hpp"
#include "HealthDisplay.hpp"
#include "Game.hpp"

#ifdef _WIN32
#define FONT "assets/font/Call me maybe.ttf"
#else
#define FONT "../assets/font/Call me maybe.ttf"
#endif

HealthDisplay::HealthDisplay(GameObject& associated, int health, PlayerController& pc)
    : Component(associated),
      text(associated, FONT, 60, TextStyle::BLENDED, "Health: " + std::to_string(health), SDL_Color{255, 0, 0, 255}),
      pc(pc) {
    }

void HealthDisplay::Update(float dt) {
        text.SetText("Health: " + std::to_string(pc.GetHealth()));
    }

void HealthDisplay::Render()  {
        associated.box.SetCenter(250, 50);
        text.RenderStatic(); 
    }

bool HealthDisplay::Is(std::string type) {
        return type == "HealthDisplay"; 
    }

