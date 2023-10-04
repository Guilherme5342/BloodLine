#include "StageState.h"
#include "Game.h"
#include "PlayerController.h"



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
	Vector2 windowCenter = Game::Instance().GetWindowCenter();

	GameObject* bgObj = new GameObject("Background");
	bgObj->AddComponent(new Sprite(*bgObj, BACKGROUND_IMAGE));
	bgObj->AddComponent(new CameraFollower(*bgObj));

	GameObject* rb = new GameObject("PlayerBody");
	rb->AddComponent(new Sprite(*rb, "assets/img/ball2.png"));

	Collider* collider = new Collider(*rb, Vector2(rb->box.w,rb->box.h));
	rb->AddComponent(collider);
	rb->AddComponent(new Rigidbody2D(*rb,10,12));
	rb->AddComponent(new PlayerController(*rb,
		*(Rigidbody2D*)rb->GetComponent("Rigidbody2D"), 300));

	rb->box.SetCenter(windowCenter - Vector2(0,200));

	Camera::Follow(rb);

	AddObject(bgObj);
	AddObject(rb);

	GameObject* groundObj = new GameObject("Ground");
	groundObj->AddComponent(new RectDebugger(*groundObj,windowCenter.x - 256,windowCenter.y,1100,150));
	groundObj->AddComponent(new Collider(*groundObj, Vector2(groundObj->box.w, groundObj->box.h)));

	AddObject(groundObj);

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


	Rect groundRect = Rect(Game::Instance().GetWindowCenter(), 500, 100);

	groundRect.FillRect();
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
		Collider* currentCol = (Collider*)objectArray[i]->GetComponent("Collider");

		if (currentCol == nullptr)
			continue;

		for (unsigned j = i + 1; j < objectArray.size(); j++)
		{
			Collider* otherCol = (Collider*)objectArray[j]->GetComponent("Collider");
			if (otherCol == nullptr)
				continue;
			
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
