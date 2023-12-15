#include "Button.h"
#include "Galapagos/Components/AnimatedSprite.hpp"
#include "Galapagos/Core/InputManager.hpp"

Button::Button(GameObject& associated, std::function<void(void)> onClick, std::string text, std::string bgFile, std::string fontFile)
	: Component (associated), m_onClick(onClick)
{
	m_text = text;

    AnimatedSprite* sprite = new AnimatedSprite(associated, bgFile);
    sprite->SetScale(2);
    associated.AddComponent(sprite);
}

Button::~Button()
{
}

void Button::Update(float deltaTime)
{
    bool isHovered = m_associated.m_box.IsColliding(InputManager::GetMousePos());

    if (isHovered) {
        if (InputManager::MousePress(MouseButton::Left)) {
            m_onClick();
        }
    }
}

void Button::Render() const
{
}
