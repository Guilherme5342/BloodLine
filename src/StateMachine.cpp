#include "StateMachine.hpp"


StateMachine::StateMachine(GameObject& associated)
: Component(associated)
{
	currentState = nullptr;

}

StateMachine::~StateMachine()
{
	while (!stateStack.empty())
	{
		stateStack.pop();
	}
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
