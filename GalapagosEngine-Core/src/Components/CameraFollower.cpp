#include "Galapagos/Components/CameraFollower.hpp"

#include "Galapagos/Core/Camera.hpp"

CameraFollower::CameraFollower(GameObject &associated) : Component(associated)
{
}

void CameraFollower::Update(float deltaTime)
{
    m_associated.m_box.x = Camera::position.x;
    m_associated.m_box.y = Camera::position.y;
}

void CameraFollower::Render() const
{
}

bool CameraFollower::Is(std::string type) const
{
    return type == "CameraFollower";
}
