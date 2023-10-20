#include "StateMachine.hpp"


StateMachine::StateMachine(GameObject& associated)
	: Component(associated)
{
}

inline void StateMachine::Update(float dt)
{
	if (currentState == nullptr) {
		return;
	}
	currentState->Update(*this, dt);
}


inline void StateMachine::Render()
{
}
