#pragma once

#include "GameObject.hpp"
#include <string>

class Component
{
public:
    Component(GameObject &associated);
    virtual ~Component();

    virtual void Start();
    virtual void Update(float deltaTime) = 0;
    virtual void NotifyCollision(GameObject& other);
    virtual void Render() const = 0;
    virtual bool Is(std::string type) const = 0;

protected:
    GameObject &m_associated;
};