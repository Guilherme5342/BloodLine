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
