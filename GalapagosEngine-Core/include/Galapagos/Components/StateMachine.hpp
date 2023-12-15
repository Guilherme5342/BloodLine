#pragma once

#include <memory>
#include <unordered_map>
#include <stack>
#include <string>

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"
#include "Galapagos/Components/AnimatedSprite.hpp"
#include "Galapagos/Interfaces/StateInterfaces.hpp"


class StateMachine : public Component {

protected:

	IState* currentState;

	std::unordered_map<std::string, bool> transitions;

	AnimatedSprite& sprite;

public:
	StateMachine(GameObject& associated, AnimatedSprite& sprite);
	virtual ~StateMachine();

	virtual void Update(float dt);
	virtual void Render() const;


	inline bool Is(std::string type) const {
		return type == "StateMachine";
	}

	inline IState& GetCurrentState() const {
		return *currentState;
	}

	void SetState(IState* newState);

	inline Vec2 GetCenter() {
		return m_associated.m_box.GetCenter();
	}

};


