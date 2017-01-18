#pragma once
#include "KeyboardKey.h"
#include "Utilities\Math\Vector2.h"



class InputCallback
{
public:
	virtual ~InputCallback();

	virtual void Update();

	virtual void MousePositionUpdate(const SB::Vector2f & aMousePosition) = 0;

	virtual void MousePressed(const SB::MouseKey aKey) = 0;
	virtual void MouseReleased(const SB::MouseKey aKey) = 0;

	virtual void KeyPressed(const SB::KeyboardKey aKey) = 0;
	virtual void KeyReleased(const SB::KeyboardKey aKey) = 0;

protected:
	InputCallback();
};

