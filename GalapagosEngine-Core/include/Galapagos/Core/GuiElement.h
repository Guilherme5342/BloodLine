#pragma once
#include <string>
#include <cstdint>
#include "Galapagos/Math/Rect.hpp"
#include "Galapagos/Core/State.hpp"

class GuiElement
{
public:
    GuiElement(State& parent, Rect box);
    virtual ~GuiElement();

    virtual void Update(float deltaTime) = 0;
    virtual void Render() const = 0;
    virtual bool Is(std::string type) const = 0;

    Rect m_box;
    bool m_isActive = true;
    bool m_isDisplayed = true;

    bool Hovering() const;

protected:
    State& m_parent;
};

