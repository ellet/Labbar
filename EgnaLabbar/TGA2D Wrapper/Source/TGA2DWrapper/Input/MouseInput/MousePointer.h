#pragma once

#include "../../BaseClasses/BaseGameObject/BaseGameObject.h"

#include <GrowingArray/GrowingArray.h>
#include "MouseAction/BaseMouseAction.h"
#include "MouseStates.h"



namespace DX2D
{
	class CSprite;
}

class MousePointer : public BaseGameObject
{
public:
	MousePointer();
	~MousePointer();

	void inline SetCurrentState(const enumMouseStates aEnumMouseState);
	enumMouseStates inline GetCurrentState();

	void TriggerClick();

	void TriggerHeld();

	void TriggerRelease();

	void VariableSetup();

	void ChangeSprite();

	virtual void Draw() const override;


	
private:
	
	std::shared_ptr<DX2D::CSprite> myNormalSprite;
	std::shared_ptr<DX2D::CSprite> myMouseOverSprite;
	std::shared_ptr<DX2D::CSprite> myMouseClickOnSprite;
	std::shared_ptr<DX2D::CSprite> myMouseItemHeld;

	CU::GrowingArray<BaseMouseAction*> myMouseActions;

	enumMouseStates myActiveState;

	bool myStateIsLocked;
};

void MousePointer::SetCurrentState(const enumMouseStates aEnumMouseState)
{
	if (myStateIsLocked == false && myActiveState != aEnumMouseState)
	{

		myActiveState = aEnumMouseState;

		ChangeSprite();
	}
}

enumMouseStates MousePointer::GetCurrentState()
{
	return myActiveState;
}