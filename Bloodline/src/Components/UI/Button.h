#pragma once
#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Components/ParticleEmmiter.hpp"
#include <functional>

class Button : public Component
{
public:
    Button(GameObject& associated, std::function<void(void)> onClick, std::string text, std::string bgFile, std::string fontFile = "");
    ~Button();

    void Update(float deltaTime) override;
    void Render() const override;
    inline bool Is(std::string type) const override { return type == "Button"; }
private:
    std::string m_text;

    std::function<void(void)> m_onClick;

    ParticleConfig m_particleConfig;
};

