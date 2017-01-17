#pragma once
#include "KeyboardKey.h"



class InputCallback
{
public:
	virtual ~InputCallback();
	virtual void KeyPressed(const SB::KeyboardKey aKey) = 0;
	virtual void KeyReleased(const SB::KeyboardKey aKey) = 0;

protected:
	InputCallback();
};

