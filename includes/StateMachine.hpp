#pragma once

#include "Component.hpp"

class StateMachine : public Component {

public:
	virtual ~StateMachine(){ }

	virtual void Enter(GameObject& otherObj) = 0;
	virtual void Exit(GameObject& otherObj) = 0;
};