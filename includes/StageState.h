#pragma once

#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "Rigidbody2D.h"
#include "RectDebug.h"

#ifdef _WIN32
#define BACKGROUND_IMAGE "assets/img/ocean.jpg"
#else
#define BACKGROUND_IMAGE "../assets/img/ocean.jpg"
#endif

class StageState : public State
{

private:
	Sprite *bg;
	Music *music;

public:
	StageState();
	//~StageState();
	// Herdado por meio de State
	virtual void LoadAssets() override;
	virtual void Pause() override;
	virtual void Resume() override;
	virtual void Start() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
};