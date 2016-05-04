#pragma once
#include "MousePointer.h"
#include <Vectors/vector2.h>
#include <DLDebug/DL_Debug.h>
#include "../MouseActions/ActionWheel.h"

#include "../../CollisionManager/CollisionShapes/PointShape.h"



class OnMouseHoverTriggerCollider;
class Object;
class Inventory;

class MouseInput
{
public:
	static void Create();
	static void Destroy();

	static Vector2f inline GetMousePosition();

	static void inline SetMouseState(const enumMouseStates aMouseStateToSet);
	static enumMouseStates inline GetMouseState();

	static void inline PrepareActionWheel();
	static void inline ActivateWheel();

	static bool inline GetWheelState();

	static void inline Update();
	static void inline Draw();

	static void inline MouseCollided();

	static void inline SetMouseDefaultState(const enumMouseStates aMouseState);

	static void inline SetObjectRefrenceOnWheel(Object* aObject);
	static inline ActionWheel& GetActionWheel();

	static void inline SetInventoryPointer(Inventory * aInventoryPointer);
	static inline Inventory & GetInventoryPointer();

	static void inline ActiveElementOnActionWheel(const eElementType aElementToActive);

private:
	MouseInput();
	~MouseInput();

	static inline MouseInput & GetInstance();

	void InsideUpdate();
	void VariableSetup();

	PointShape myCollisionShape;
	OnMouseHoverTriggerCollider * myHoverTrigger;

	bool myMouseHasCollided;
	bool myActionWheelWasActiveThisFrame;

	static MouseInput * ourInstance;
	MousePointer myPointer;
	ActionWheel myActionWheel;
	enumMouseStates myNeutralState;

	Inventory * myInventoryPointer;
};

void MouseInput::PrepareActionWheel()
{
	if (GetInstance().myActionWheelWasActiveThisFrame == false)
	{
		GetInstance().myActionWheel.PreparePositions();
	}
}

void MouseInput::ActivateWheel()
{
	if (GetInstance().myActionWheelWasActiveThisFrame == false)
	{
		GetInstance().myActionWheel.SetIsActive();
	}
}

MouseInput & MouseInput::GetInstance()
{
	DL_ASSERT(ourInstance != false, "Mouse input instance is nullptr");
	return (*ourInstance);
}

void MouseInput::Draw()
{
	GetInstance().myActionWheel.Draw();
	GetInstance().myPointer.Draw();
}

void MouseInput::Update()
{
	GetInstance().InsideUpdate();
}

Vector2f MouseInput::GetMousePosition()
{
	return GetInstance().myPointer.GetPosition();
}

void MouseInput::SetMouseState(enumMouseStates aMouseStateToSet)
{
	GetInstance().myPointer.SetCurrentState(aMouseStateToSet);
}

void MouseInput::SetMouseDefaultState(const enumMouseStates aMouseState)
{
	GetInstance().myNeutralState = aMouseState;
}

inline void MouseInput::MouseCollided()
{
	GetInstance().myMouseHasCollided = true;
}

inline void MouseInput::SetObjectRefrenceOnWheel(Object* aObject)
{
	GetInstance().myActionWheel.SetActiveObject(aObject);
}

inline enumMouseStates MouseInput::GetMouseState()
{
	return GetInstance().myPointer.GetCurrentState();
}

inline bool MouseInput::GetWheelState()
{
	return GetInstance().myActionWheel.GetActiveState();
}


inline ActionWheel& MouseInput::GetActionWheel()
{
	return GetInstance().myActionWheel;
}

inline void MouseInput::SetInventoryPointer(Inventory * aInventoryPointer)
{
	GetInstance().myInventoryPointer = aInventoryPointer;
}

inline Inventory & MouseInput::GetInventoryPointer()
{
	return *GetInstance().myInventoryPointer;
}

inline void MouseInput::ActiveElementOnActionWheel(const eElementType aElementToActive)
{
	GetInstance().myActionWheel.ActivateElementalAction(aElementToActive);
}