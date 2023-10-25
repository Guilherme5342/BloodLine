#pragma once

#include "Sprite.hpp"

class StateMachine;

class IState {

public:
	virtual ~IState() {}
	virtual void OnEnter(StateMachine& otherState) {}
	virtual void OnExit(StateMachine& otherState) {}

	virtual void Update(StateMachine& state, float dt) = 0;
	virtual void Render(StateMachine& state) = 0;
};


class AnimState : public IState {

private:
	Sprite& spriteAnim;

public:
	AnimState(Sprite& sprite, std::string animFile);
	void Play(std::string animFile);
};
