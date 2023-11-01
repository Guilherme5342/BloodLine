#pragma once

#include "State.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include "Rigidbody2D.hpp"
#include "RectDebug.hpp"
#include "PlayerController.hpp"
#include "StateMachine.hpp"
#include "GlobalDefinitions.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"


#ifdef _WIN32
#define BACKGROUND_IMAGE "assets/img/ocean.jpg"
#else
#define BACKGROUND_IMAGE "../assets/img/ocean.jpg"
#endif

class StageState : public State
{

private:
	//Sprite *bg;
	Music music;

public:
	StageState();
	~StageState();
	// Herdado por meio de State
	virtual void LoadAssets() override;
	virtual void Pause() override;
	virtual void Resume() override;
	virtual void Start() override;
	virtual void FixedUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void Render() override;
};