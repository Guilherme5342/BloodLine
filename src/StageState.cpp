#include "StageState.h"


StageState::StageState() : State()
{
	Vector3 vector = Vector3(1, 1, 1);
	Vector2 vec2d_1 = Vector2(2, 3);
	Vector3 vec2d_2 = Vector2(1, 3);

	Vector2 s = vec2d_1;

	cout << vector << endl;
	cout << vec2d_1 << endl;
	cout << vec2d_2 << endl;
}

void StageState::LoadAssets()
{
	GameObject* bgObj = new GameObject("Background");
	bgObj->AddComponent(new Sprite(*bgObj, BACKGROUND_IMAGE));
	bgObj->AddComponent(new CameraFollower(*bgObj));

	GameObject* rb = new GameObject("Body");
	rb->AddComponent(new Sprite(*rb, "assets/img/ball2.png"));
	rb->AddComponent(new Rigidbody2D(*rb));

	AddObject(bgObj);
	AddObject(rb);
}

void StageState::Pause()
{
}

void StageState::Resume()
{
}

void StageState::Start()
{
	StartArray();
	started = true;

}

void StageState::Update(float dt)
{
	if (InputSystem::Instance().KeyPress(SDLK_ESCAPE)) {
		popRequested = true;
	}
	
	Camera::Update(dt);

	UpdateArray(dt);

	for (unsigned i = 0; i < objectArray.size(); i++)
	{
		Collider* currentCol = nullptr;
		
		if(!objectArray[i]->TryGetComponent<Collider>("Collider", currentCol))
			continue;

		for (unsigned j = i + 1; j < objectArray.size(); j++)
		{
			Collider* otherCol = (Collider*)objectArray[j]->GetComponent("Collider");
			if (Collision::IsColliding(currentCol->box, otherCol->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg))
			{
				objectArray[i]->NotifyCollision(*objectArray[j]);
				objectArray[j]->NotifyCollision(*objectArray[i]);
			}
		}
	}
}

void StageState::Render()
{
	RenderArray();
}
