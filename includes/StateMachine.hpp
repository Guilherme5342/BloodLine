#pragma once

#include "Component.hpp"
#include <stack>

class StateMachine;

class IState {

public:
	virtual ~IState(){}
	virtual void Enter(StateMachine& otherState) = 0;
	virtual void Exit(StateMachine& otherState) = 0;

	virtual void Update(StateMachine& state, float dt) = 0;
};

class StateMachine : public Component {

private:
	std::stack<std::shared_ptr<IState>> stateStack;

	IState* currentState;
public:
	StateMachine(GameObject& associated);
	virtual ~StateMachine(){ }

	virtual void Update(float dt);
	virtual void Render();

	inline bool Is(std::string type) {
		return type == "StateMachine";
	}

	inline IState& GetCurrentState() {
		return *stateStack.top();
	}

	inline void AddState(IState* newState) {
		if (currentState != nullptr) {
			currentState->Exit(*this);
		}
		
		currentState = newState;
		newState->Enter(*this);

		stateStack.emplace(newState);
	}

	inline void RemoveState(IState* state) {

	}
};


