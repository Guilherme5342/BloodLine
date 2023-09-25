#include "CameraFollower.h"
#include "GameObject.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& associated) : Component(associated)
{
}

void CameraFollower::Update(float dt)
{
	associated.box.x = Camera::GetCurrentCamPos().x;
	associated.box.y = Camera::GetCurrentCamPos().y;
}

void CameraFollower::Render()
{
}