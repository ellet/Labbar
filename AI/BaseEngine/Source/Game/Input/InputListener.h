#pragma once
#include "tga2d\Input\InputCallback.h"


class InputListener : public InputCallback
{
public:
	InputListener();
	~InputListener();

	void SetAsListener();

	virtual void KeyPressed(const SB::KeyboardKey aKey) override;
	virtual void KeyReleased(const SB::KeyboardKey aKey) override;

private:
};

