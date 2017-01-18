#pragma once

#include "InputCallback.h"
#include "Utilities\Container\GrowingArray.h"
#include "Utilities\Math\Vector2.h"


class InputListener : public InputCallback
{
public:
	InputListener();
	~InputListener();

	void Update() override;

	const SB::Vector2f & GetMousePosition() const;

	bool GetIfMouseButtonPressed(const SB::MouseKey aKey);
	bool GetIfMouseButtonReleased(const SB::MouseKey aKey);
	bool GetIfMouseButtonDown(const SB::MouseKey aKey);

	bool GetIfKeyPressed(const SB::KeyboardKey aKey);
	bool GetIfKeyReleased(const SB::KeyboardKey aKey);
	bool GetIfKeyDown(const SB::KeyboardKey aKey);

	virtual void KeyPressed(const SB::KeyboardKey aKey) override;
	virtual void KeyReleased(const SB::KeyboardKey aKey) override;

	virtual void MousePositionUpdate(const SB::Vector2f & aMousePosition) override;
	virtual void MousePressed(const SB::MouseKey aKey) override;
	virtual void MouseReleased(const SB::MouseKey aKey) override;

private:
	SB::Vector2f myMousePosition;

	SB::GrowingArray<bool> myCurrentMouseButtonStates;
	SB::GrowingArray<bool> myPreviousMouseButtonStates;

	SB::GrowingArray<bool> myCurrentKeyStates;
	SB::GrowingArray<bool> myPreviousKeyStates;
};

