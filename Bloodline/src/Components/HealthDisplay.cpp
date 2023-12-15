#include "Galapagos/Components/Text.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Components/PlayerController.hpp"
#include "Components/HealthDisplay.hpp"
#include "Galapagos/Core/Game.hpp"

#ifdef _WIN32
#define FONT "res/font/Seagram tfb.ttf"
#else
#define FONT "../res/font/Seagram tfb.ttf"
#endif

HealthDisplay::HealthDisplay(GameObject &associated, int health, PlayerController &pc)
    : Component(associated),
      m_text(associated, 60, Text::Style::BLENDED, "Health " + std::to_string(health), SDL_Color{255, 0, 0, 255}, FONT),
      m_pc(pc)
{
}

void HealthDisplay::Update(float dt)
{
        m_text.SetText("Health " + std::to_string(m_pc.GetHealth()));
}

void HealthDisplay::Render() const
{
        m_associated.m_box.SetCenter(Vec2(250, 50));
        m_text.RenderStatic();
}
