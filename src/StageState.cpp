#include "StageState.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "PawnEnemy.hpp"
#include "HealthDisplay.hpp"
#include "ColorDefinitions.hpp"

StageState::StageState() : State()
{
}

StageState::~StageState()
{
	objectArray.clear();
	std::cout << "StageState" << std::endl;
}

void StageState::AddGround(Vector2 pos, Vector2 size, SDL_Color color) 
{
	GameObject* rectObj = new GameObject("RectGround", "Ground",1);
	RectDebugger* newGroundDebug = new RectDebugger(*rectObj, pos.x, pos.y, size.x, size.y, color);
	rectObj->AddComponent(newGroundDebug);
	rectObj->AddComponent(new Collider(*rectObj));
	AddObject(rectObj);
}

void StageState::LoadAssets()
{

	music.Open("assets/audio/stageState.ogg");

	Vector2 windowCenter = Game::GetWindowCenter();

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
	groundObj->AddComponent(new RectDebugger(*groundObj, windowCenter.x, windowCenter.y, 1100, 150));
	groundObj->AddComponent(new Collider(*groundObj, Vector2(groundObj->box.w, groundObj->box.h)));

	AddObject(groundObj);

	AddGround(Vector2(windowCenter.x + 512, 512), Vector2(500, 110));
	AddGround(Vector2(windowCenter.x + groundObj->box.x, 512), Vector2(750, 110), Color::Red);
	AddGround(Vector2(windowCenter.x + 128, 256), Vector2(500, 110), Color::Yellow);
	AddGround(Vector2(windowCenter.x + 1024, 256), Vector2(500, 110), Color::Magenta);

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
	std::cout << "StageState " << objectArray.size() << std::endl;

	Rect groundRect = Rect(Game::GetWindowCenter(), 500, 100);

	groundRect.FillRect();

	tileMap->LoadCollisions();
	tileMap->SetParallaxFactor(Vector2(.5f, 1));
}

void StageState::FixedUpdate(float fixedDt)
{
	FixedUpdateArray(fixedDt);
}

void StageState::Update(float dt)
{
	if (InputSystem::KeyPress(SDLK_ESCAPE))
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
