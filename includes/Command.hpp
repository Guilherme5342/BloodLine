#pragma once

#include "GameObject.hpp"

class Command
{

public:
	virtual ~Command();
	virtual void Execute(GameObject &associated) = 0;
};

class JumpCommand : public Command
{

public:
	JumpCommand();
	void Execute(GameObject &as)
	{
	}
};