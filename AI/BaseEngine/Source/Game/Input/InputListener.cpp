#include "stdafx.h"
#include "InputListener.h"
#include "tga2d\engine.h"
#include "tga2d\windows\windows_window.h"


InputListener::InputListener()
{
}


InputListener::~InputListener()
{
}

void InputListener::SetAsListener()
{
	DX2D::CEngine::GetInstance()->GetWindow().SetInputCallback(*this);
}

void InputListener::KeyPressed(const SB::KeyboardKey aKey)
{
	int apa = 10;
	++apa;
}

void InputListener::KeyReleased(const SB::KeyboardKey aKey)
{
	int apa = 10;
	++apa;
}
