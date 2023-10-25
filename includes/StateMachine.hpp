#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

#include <memory>
#include <unordered_map>
#include <stack>

class StateMachine;

class IState {

public:
	virtual ~IState(){}
	virtual void OnEnter(StateMachine& otherState) {};
	virtual void OnExit(StateMachine& otherState) {};

	virtual void Update(StateMachine& state, float dt) = 0;
	virtual void Render(StateMachine& state) = 0;
};

class StateMachine : public Component {

private:

	IState* currentState;

	std::unordered_map<string, bool> transitions;
	

public:
	StateMachine(GameObject& associated);
	virtual ~StateMachine();

	virtual void Update(float dt);
	virtual void Render();

	inline bool Is(std::string type) {
		return type == "StateMachine";
	}

	inline IState& GetCurrentState() {
		return *currentState;
	}

	inline void AddState(IState* newState) {

		if (currentState != nullptr) {
			GetCurrentState().OnExit(*this);
		}
			
		currentState = newState;

		GetCurrentState().OnEnter(*this);
	}

	inline Vector2 GetCenter() {
		return associated.box.GetCenter();
	}

};


