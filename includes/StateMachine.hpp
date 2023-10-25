#pragma once

#include <memory>
#include <unordered_map>
#include <stack>

#include "Component.hpp"
#include "GameObject.hpp"
#include "Sprite.h"
#include "StateInterfaces.hpp"

class StateMachine : public Component {

private:

	IState* currentState;

	std::unordered_map<string, bool> transitions;

	Sprite& sprite;

public:
	StateMachine(GameObject& associated, Sprite& sprite);
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


