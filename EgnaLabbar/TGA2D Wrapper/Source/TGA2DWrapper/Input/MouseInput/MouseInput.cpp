#include "MouseInput.h"
#include "../../Utility/MouseInputResolutionAdaption.h"
#include <InputWrapper/InputWrapper.h>
#include "../../CollisionManager/CollisionManager.h"
#include "../../CollisionManager/CollisionShapes/PointShape.h"

#include "../../CollisionManager/TriggerColliders/OnMouseHoverTriggerCollider.h"

MouseInput * MouseInput::ourInstance;


void MouseInput::Create()
{
	ourInstance = new MouseInput();
	ShowCursor(false);

	GetInstance().myPointer.VariableSetup();
}

void MouseInput::Destroy()
{
	delete ourInstance;

	ourInstance = nullptr;
}






void MouseInput::InsideUpdate()
{
	myActionWheelWasActiveThisFrame = myActionWheel.GetActiveState();

	myPointer.SetPosition(MouseFix::GetFixedMousePosition());

	myCollisionShape.ChangePosition(myPointer.GetPosition());

	if (myMouseHasCollided == false && 
		myPointer.GetCurrentState() != enumMouseStates::eTalkMode &&
		myPointer.GetCurrentState() != enumMouseStates::eHoldingItem)
	{
		myPointer.SetCurrentState(myNeutralState);
	}
	else
	{
		myMouseHasCollided = false;
	}

	if (myPointer.GetCurrentState() != enumMouseStates::eTalkMode &&
		myPointer.GetCurrentState() != enumMouseStates::eHoldingItem)
	{
		CollisionManager::AddATriggerCollider(*myHoverTrigger);
	}

	myActionWheel.Update();

	if (CU::InputWrapper::GetMouseButtonPressed(CU::enumMouseButtons::eRight) == true)
	{
		myPointer.TriggerClick();
	}

	if (CU::InputWrapper::GetMouseButtonDown(CU::enumMouseButtons::eRight) == true)
	{
		myPointer.TriggerHeld();
	}

	if (CU::InputWrapper::GetMouseButtonReleased(CU::enumMouseButtons::eRight) == true)
	{
		if (myActionWheel.GetActiveState() == true)
		{
			myActionWheel.SetIsDisabled();
		}

		myPointer.TriggerRelease();

		if (myPointer.GetCurrentState() == enumMouseStates::eHoldingItem)
		{
			myPointer.SetCurrentState(enumMouseStates::eNeutralMode);
		}
	}
}




MouseInput::MouseInput()
{
	myNeutralState = enumMouseStates::eMovePlayerMode;

	myCollisionShape = PointShape(Vector2f::Zero);
	myHoverTrigger = new OnMouseHoverTriggerCollider(myCollisionShape);
	myMouseHasCollided = false;
	myActionWheelWasActiveThisFrame = false;
}


MouseInput::~MouseInput()
{
}