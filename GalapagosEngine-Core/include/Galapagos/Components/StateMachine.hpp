#pragma once

#include <memory>
#include <unordered_map>
#include <stack>
#include <string>

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Interfaces/StateInterfaces.hpp"


class StateMachine : public Component {

protected:

	IState* currentState;

	std::unordered_map<std::string, bool> transitions;

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

	void SetState(IState* newState);

	inline Vec2 GetCenter() {
		return m_associated.m_box.GetCenter();
	}

};

