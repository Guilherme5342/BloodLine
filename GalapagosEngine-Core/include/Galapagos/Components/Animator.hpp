#pragma once

#include <unordered_map>
#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Utils/Sprite.h"

class Animator : public Component {
public:
    Animator(GameObject& associated);

    void AddAnimation(std::string name, std::string animationFile);

    void Update(float deltaTime) override;
    void Render() const override;
    inline bool Is(std::string type) const override { return type == "Animator"; }
private:
    std::unordered_map<std::string, Sprite*> m_animationMap;
    Sprite* m_activeAnimation;
};