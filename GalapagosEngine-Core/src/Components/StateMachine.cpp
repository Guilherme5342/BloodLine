#include "Galapagos/Components/StateMachine.hpp"


StateMachine::StateMachine(GameObject& associated, AnimatedSprite& sprite)
: Component(associated) , sprite(sprite)
{
	currentState = nullptr;

}

StateMachine::~StateMachine()
{

}

void StateMachine::Update(float dt)
{
	if (currentState == nullptr) {
		return;
	}
	GetCurrentState().Update(*this, dt);
}


void StateMachine::Render() const
{
	if (currentState == nullptr) {
		return;
	}
	GetCurrentState().Render(*this);
}


void StateMachine::SetState(IState* newState)
{
	if (currentState != nullptr) {
		GetCurrentState().OnExit(*this);
	}

	currentState = newState;

	GetCurrentState().OnEnter(*this);
}
