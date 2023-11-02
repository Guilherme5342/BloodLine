#include "StageState.hpp"
#include "Game.hpp"
#include "Resources.hpp"

StageState::StageState() : State()
{
}

StageState::~StageState()
{
	objectArray.clear();
	cout << "StageState" << endl;
	//Resources::ClearAll();
}

void StageState::LoadAssets()
{

	music.Open("assets/audio/stageState.ogg");

	Vector2 windowCenter = Game::Instance().GetWindowCenter();

	GameObject *bgObj = new GameObject("Background");
	bgObj->AddComponent(new Sprite(*bgObj, BACKGROUND_IMAGE));
	bgObj->AddComponent(new CameraFollower(*bgObj));

	GameObject* tileObj = new GameObject("TileObject");
	TileSet* tileSet = new TileSet(*tileObj,32,32,TILESET_WATER_STUB);
	tileMap = new TileMap(*tileObj, MAP_STUB, tileSet);

	tileObj->AddComponent(tileMap);

	


    /* Criação do Player*/
	GameObject *rb = new GameObject("PlayerBody",1);
	rb->AddComponent(new Sprite(*rb, BALL_PNG,3,2,.5f));

	Collider *collider = new Collider(*rb, Vector2(rb->box.w, rb->box.h));
	rb->AddComponent(collider);
	rb->AddComponent(new Rigidbody2D(*rb, 100, 100));
	//rb->AddComponent(new StateMachine(*rb, *(Sprite*)rb->GetComponent("Sprite")));

	rb->AddComponent(new PlayerController(*rb,
		*(Sprite*)rb->GetComponent("Sprite"), 
		*(Rigidbody2D*)rb->GetComponent("Rigidbody2D"), 300));


	rb->box.SetCenter(windowCenter - Vector2(0, 200));

	Camera::Follow(rb);

	AddObject(bgObj);
	AddObject(tileObj);
	AddObject(rb);

	GameObject *groundObj = new GameObject("Ground", 1);
	groundObj->AddComponent(new RectDebugger(*groundObj, windowCenter.x - 256, windowCenter.y, 1100, 150));
	groundObj->AddComponent(new Collider(*groundObj, Vector2(groundObj->box.w, groundObj->box.h)));


	AddObject(groundObj);

	//tileMap->LoadCollisions();
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

	music.Play();
	cout << "StageState " << objectArray.size() << endl;

	Rect groundRect = Rect(Game::Instance().GetWindowCenter(), 500, 100);

	groundRect.FillRect();

	tileMap->LoadCollisions();

}

void StageState::FixedUpdate(float fixedDt) {

	FixedUpdateArray(fixedDt);
}

void StageState::Update(float dt)
{
	if (InputSystem::Instance().KeyPress(SDLK_ESCAPE))
	{
		popRequested = true;
	}
	Camera::Update(dt);
	UpdateArray(dt);

	
}

void StageState::Render()
{
	RenderArray();
}
