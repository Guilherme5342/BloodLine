#pragma once
#include <vector>
#include <string>
#include <memory>

#include "math/Rect.h"
#include "math/Vec2.h"

class Component;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    void Start();
    void Update(float deltaTime);
    void NotifyCollision(GameObject& other);
    void Render() const;
    bool IsDead() const;
    void RequestDelete();
    void AddComponent(Component *component);
    void RemoveComponent(Component *component);
    Component *GetComponent(std::string type) const;

    Rect m_box;
    double m_angleDeg;

private:
    std::vector<std::unique_ptr<Component>> m_componentList;
    bool m_isDead;
    bool m_started;
};