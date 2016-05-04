#pragma once
#include "MousePointer.h"
#include <Vectors/vector2.h>
#include <DLDebug/DL_Debug.h>







class MouseInput
{
public:
	static void Create();
	static void Destroy();

	static Vector2f inline GetMousePosition();
	static void inline SetMouseState(enumMouseStates aMouseStateToSet);

	static void inline Update();
	static void inline Draw();

private:
	MouseInput();
	~MouseInput();

	static inline MouseInput & GetInstance();
	void InsideUpdate();

	void VariableSetup();

	bool myTestBool;

	static MouseInput * ourInstance;

	MousePointer myPointer;


	

	
};

MouseInput & MouseInput::GetInstance()
{
	DL_ASSERT(ourInstance != false, "Mouse input instance is nullptr");
	return (*ourInstance);
}

void MouseInput::Draw()
{
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