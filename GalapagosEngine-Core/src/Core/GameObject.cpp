#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Core/Component.hpp"

#ifdef DEBUG
    #include <SDL2/SDL.h>
    #include "Galapagos/Core/Game.hpp"
    #include "Galapagos/Core/Camera.hpp"
#endif // DEBUG

GameObject::GameObject()
{
    m_isDead = false;
    m_started = false;
    m_angleDeg = 0.0;
}

GameObject::~GameObject()
{
    m_componentList.clear();
}

void GameObject::Start()
{
    for (size_t i = 0; i < m_componentList.size(); i++)
    {
        m_componentList[i]->Start();
    }
    m_started = true;
}

void GameObject::FixedUpdate(float fixedDt)
{
    for (size_t i = 0; i < m_componentList.size(); i++)
    {
        m_componentList[i]->FixedUpdate(fixedDt);
    }
}

void GameObject::Update(float deltaTime)
{
    for (size_t i = 0; i < m_componentList.size(); i++)
    {
        m_componentList[i]->Update(deltaTime);
    }
}

void GameObject::NotifyCollision(GameObject &other)
{
    for (size_t i = 0; i < m_componentList.size(); i++)
    {
        m_componentList[i]->NotifyCollision(other);
    }
}

void GameObject::Render() const
{
    for (size_t i = 0; i < m_componentList.size(); i++)
    {
        m_componentList[i]->Render();
    }
#ifdef DEBUG
    SDL_SetRenderDrawBlendMode(Game::GetRenderer(), SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(Game::GetRenderer(), 0, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_Rect distRect = { m_box.x - Camera::position.x, m_box.y - Camera::position.y, m_box.w, m_box.h };
    SDL_RenderDrawRect(Game::GetRenderer(), &distRect);
#endif // DEBUG
}

bool GameObject::IsDead() const
{
    return m_isDead;
}

void GameObject::RequestDelete()
{
    m_isDead = true;
}

void GameObject::AddComponent(Component *component)
{
    m_componentList.emplace_back(component);

    if (m_started)
        component->Start();
}

void GameObject::RemoveComponent(Component *component)
{
    for (auto it = m_componentList.begin(); it != m_componentList.end(); it++)
    {
        if (it->get() == component)
        {
            m_componentList.erase(it);
            return;
        }
    }
}

Component *GameObject::GetComponent(std::string type) const
{
    for (size_t i = 0; i < m_componentList.size(); i++)
    {
        if (m_componentList[i]->Is(type))
            return m_componentList[i].get();
    }
    return nullptr;
}