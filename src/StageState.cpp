#include "StageState.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "PawnEnemy.hpp"
#include "HealthDisplay.hpp"

StageState::StageState() : State()
{
}

StageState::~StageState()
{
	objectArray.clear();
	cout << "StageState" << endl;
}

void StageState::LoadAssets()
{

	music.Open("assets/audio/stageState.ogg");

	Vector2 windowCenter = Game::Instance().GetWindowCenter();

	GameObject *bgObj = new GameObject("Background");
	bgObj->AddComponent(new Sprite(*bgObj, BACKGROUND_IMAGE));
	bgObj->AddComponent(new CameraFollower(*bgObj));

	GameObject *tileObj = new GameObject("TileObject",1);
	TileSet *tileSet = new TileSet(*tileObj, 32, 32, TILESET_WATER_STUB);
	tileMap = new TileMap(*tileObj, MAP_STUB, tileSet);

	tileObj->AddComponent(tileMap);
	

	/* Cria��o do Player*/
	GameObject *rb = new GameObject("PlayerBody", 1);
	Sprite* playerSprite = new Sprite(*rb, BALL_PNG, 3, 2, .1f);
	playerSprite->SetLoop(true);
	rb->AddComponent(playerSprite);

	Collider* collider = new Collider(*rb);
	collider->SetScale({ 25,35 });

	rb->AddComponent(collider);
	rb->AddComponent(new Rigidbody2D(*rb, 100, 100));

	PlayerController *pc = new PlayerController(*rb,
					*playerSprite,
					*(Rigidbody2D*)rb->GetComponent("Rigidbody2D"), 300);


	rb->AddComponent(pc);

	rb->box.SetCenter(windowCenter - Vector2(0, 200));

	Camera::Follow(rb);

	// Enemies 
	GameObject* enemyObj = new GameObject("Enemy1");
	Sprite* enemySprite = new Sprite(*enemyObj, "assets/img/enemies/knight/_Idle.png", 10, 1, .3f);
	enemySprite->SetLoop(true);

	EnemyBase* enemyTest = new PawnEnemy(*enemyObj, GetObjectPtr(rb),
		*enemySprite, 10, 1, IDLE, GROUND, 4);

	enemyObj->AddComponent(enemyTest);

	enemyObj->box.SetCenter(rb->box.GetCenter() + Vector2(20, 0));

	enemyTest->GetHitBox().SetScale(25, 50);

	AddObject(bgObj);
	AddObject(tileObj);
	AddObject(enemyObj);
	AddObject(rb);

	GameObject *groundObj = new GameObject("FirstGround","Ground", 1);
	groundObj->AddComponent(new RectDebugger(*groundObj, windowCenter.x - 256, windowCenter.y, 1100, 150));
	groundObj->AddComponent(new Collider(*groundObj, Vector2(groundObj->box.w, groundObj->box.h)));

	AddObject(groundObj);

	GameObject *healthDisplayObj = new GameObject("HealthDisplay");
    HealthDisplay* healthDisplay = new HealthDisplay(*healthDisplayObj, 100, *pc);
    healthDisplayObj->AddComponent(healthDisplay);

	AddObject(healthDisplayObj);



	// tileMap->LoadCollisions();
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
	//tileMap->SetParallaxFactor(Vector2(.5f, 1));
}

void StageState::FixedUpdate(float fixedDt)
{

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
