#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

#include <stack>

class StateMachine;

class IState {


public:
	virtual ~IState(){}
	virtual void Enter(StateMachine& otherState) = 0;
	virtual void Exit(StateMachine& otherState) = 0;

	virtual void Update(StateMachine& state, float dt) = 0;
	virtual void Render(StateMachine& state) = 0;
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
			GetCurrentState().Exit(*this);
		}
		if(!stateStack.empty())
			stateStack.pop();

		currentState = newState;
		stateStack.emplace(newState);

		GetCurrentState().Enter(*this);
	}

	inline void RemoveState(IState* state) {

	}
};


