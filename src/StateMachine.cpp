#include "StateMachine.hpp"


StateMachine::StateMachine(GameObject& associated)
	: Component(associated)
{
	currentState = nullptr;

}

inline void StateMachine::Update(float dt)
{
	if (currentState == nullptr) {
		return;
	}
	GetCurrentState().Update(*this, dt);
}


inline void StateMachine::Render()
{
	if (currentState == nullptr) {
		return;
	}
	GetCurrentState().Render(*this);
}
