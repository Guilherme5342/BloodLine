#pragma once

#include "Galapagos/Components/Sprite.hpp"

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

protected:
	Sprite& spriteAnim;

public:
	AnimState(Sprite& sprite);
	void Play(std::string animFile,int columns = 1,int rows = 1);
};
