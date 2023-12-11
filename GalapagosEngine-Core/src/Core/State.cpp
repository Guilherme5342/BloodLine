#include "Galapagos/Core/State.h"

#include "Galapagos/Core/GameObject.h"

State::State()
{
    m_popRequested = false;
    m_quitRequested = false;
    m_started = false;
}

State::~State()
{
    m_objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject *object)
{
    std::shared_ptr<GameObject> objPtr(object);
    m_objectArray.push_back(objPtr);

    if (m_started)
        objPtr->Start();

    return std::weak_ptr<GameObject>(objPtr);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *object)
{
    for (size_t i = 0; i < m_objectArray.size(); i++)
    {
        if (m_objectArray[i].get() == object)
        {
            return std::weak_ptr<GameObject>(m_objectArray[i]);
        }
    }
    return std::weak_ptr<GameObject>();
}

void State::StartArray()
{
    for (size_t i = 0; i < m_objectArray.size(); i++)
    {
        m_objectArray[i]->Start();
    }
}

void State::UpdateArray(float deltaTime)
{
    for (size_t i = 0; i < m_objectArray.size(); i++)
    {
        m_objectArray[i]->Update(deltaTime);
    }
}

void State::RenderArray() const
{
    for (auto &gameObject : m_objectArray)
    {
        gameObject->Render();
    }
}
