#include "CameraFollower.h"
#include "GameObject.h"
#include "Camera.h"

void CameraFollower::Update(float dt)
{
	associated.box.SetCenter(Camera::GetCurrentCamPos());
}

void CameraFollower::Render()
{
}