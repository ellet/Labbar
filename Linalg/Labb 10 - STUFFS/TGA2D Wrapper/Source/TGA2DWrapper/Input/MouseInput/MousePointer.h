#pragma once

#include "../../BaseClasses/BaseGameObject/BaseGameObject.h"

#include <GrowingArray/GrowingArray.h>

enum class enumMouseStates
{
	eClickOnStuffMode,
	eMovePlayerMode,
	enumlength
};

class MousePointer : public BaseGameObject
{
public:
	MousePointer();
	~MousePointer();

	void inline SetCurrentState(const enumMouseStates aEnumMouseState);
	enumMouseStates inline GetCurrentState();

	void TriggerClick();

	void VariableSetup();
	
private:


	enumMouseStates myActiveState;
};

void MousePointer::SetCurrentState(const enumMouseStates aEnumMouseState)
{
	myActiveState = aEnumMouseState;
}

enumMouseStates MousePointer::GetCurrentState()
{
	return myActiveState;
}