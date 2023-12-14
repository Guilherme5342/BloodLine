#include "Galapagos/Components/StateMachine.hpp"


StateMachine::StateMachine(GameObject& associated, Sprite& sprite)
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


void StateMachine::Render()
{
	if (currentState == nullptr) {
		return;
	}
	GetCurrentState().Render(*this);
}
