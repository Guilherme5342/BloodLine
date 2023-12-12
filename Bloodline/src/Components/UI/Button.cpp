#include "Button.h"
#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Components/Text.hpp"
#include "Galapagos/Core/InputManager.hpp"

Button::Button(GameObject& associated, std::function<void(void)> onClick, std::string text, std::string bgFile, std::string fontFile)
	: Component (associated), m_onClick(onClick)
{
	m_text = text;

    Sprite* sprite = new Sprite(associated, bgFile);
    associated.AddComponent(sprite);

    Text* textComp = new Text(associated, 30, Text::Style::BLENDED, text, SDL_Color{ 63, 72, 204, 255 });
    associated.AddComponent(textComp);

    ParticleEmmiter* partEmm = new ParticleEmmiter(associated, 1000);
    associated.AddComponent(partEmm);

    m_particleConfig.lifeTime = 5.f;
    m_particleConfig.startColor = {0, 150, 200, 100};
    m_particleConfig.startSize = 20;
    m_particleConfig.sizeVariation = 10;
    m_particleConfig.velocity = { 0, 50 };
    m_particleConfig.velocityVariation = { 100, 100 };
}

Button::~Button()
{
}

void Button::Update(float deltaTime)
{
    m_particleConfig.position = m_associated.m_box.GetCenter();
    m_particleConfig.startColor.b++;
    bool isHovered = m_associated.m_box.IsColliding(InputManager::GetMousePos());
    auto emiterComponent = static_cast<ParticleEmmiter*>(m_associated.GetComponent("ParticleEmmiter"));

    if (isHovered) {
        if (InputManager::MousePress(MouseButton::Left)) {
            m_onClick();
        }
        if (emiterComponent) {
            emiterComponent->Emit(m_particleConfig);
        }
    }
}

void Button::Render() const
{
}
