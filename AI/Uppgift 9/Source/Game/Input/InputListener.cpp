#include "stdafx.h"
#include "InputListener.h"
#include "tga2d\engine.h"
#include "tga2d\windows\windows_window.h"
#include "Game.h"


InputListener::InputListener()
{
	myCurrentKeyStates.Resize(static_cast<unsigned short>(SB::KeyboardKey::eCount) ,false);
	myPreviousKeyStates.Resize(static_cast<unsigned short>(SB::KeyboardKey::eCount), false);

	myCurrentMouseButtonStates.Resize(static_cast<unsigned short>(SB::MouseKey::eCount), false);
	myPreviousMouseButtonStates.Resize(static_cast<unsigned short>(SB::MouseKey::eCount), false);

	CGame::RegisterInputCallback(*this);
}


InputListener::~InputListener()
{
	CGame::UnregisterInputCallback(*this);
}

void InputListener::Update()
{
	myPreviousKeyStates = myCurrentKeyStates;
	myPreviousMouseButtonStates = myCurrentMouseButtonStates;
}

const SB::Vector2f & InputListener::GetMousePosition() const
{
	return myMousePosition;
}

bool InputListener::GetIfMouseButtonPressed(const SB::MouseKey aKey)
{
	return (myCurrentMouseButtonStates[static_cast<unsigned short>(aKey)] == true) && (myPreviousMouseButtonStates[static_cast<unsigned short>(aKey)] == false);
}

bool InputListener::GetIfMouseButtonReleased(const SB::MouseKey aKey)
{
	return (myCurrentMouseButtonStates[static_cast<unsigned short>(aKey)] == false) && (myPreviousMouseButtonStates[static_cast<unsigned short>(aKey)] == true);
}

bool InputListener::GetIfMouseButtonDown(const SB::MouseKey aKey)
{
	return myCurrentMouseButtonStates[static_cast<unsigned short>(aKey)];
}

bool InputListener::GetIfKeyPressed(const SB::KeyboardKey aKey)
{
	return (myCurrentKeyStates[static_cast<unsigned short>(aKey)] == true) && (myPreviousKeyStates[static_cast<unsigned short>(aKey)] == false);
}

bool InputListener::GetIfKeyReleased(const SB::KeyboardKey aKey)
{
	return (myCurrentKeyStates[static_cast<unsigned short>(aKey)] == false) && (myPreviousKeyStates[static_cast<unsigned short>(aKey)] == true);
}

bool InputListener::GetIfKeyDown(const SB::KeyboardKey aKey)
{
	return myCurrentKeyStates[static_cast<unsigned short>(aKey)];
}

void InputListener::KeyPressed(const SB::KeyboardKey aKey)
{
	myCurrentKeyStates[static_cast<unsigned short>(aKey)] = true;
}

void InputListener::KeyReleased(const SB::KeyboardKey aKey)
{
	myCurrentKeyStates[static_cast<unsigned short>(aKey)] = false;
}

void InputListener::MousePositionUpdate(const SB::Vector2f & aMousePosition)
{
	myMousePosition = aMousePosition;
}

void InputListener::MousePressed(const SB::MouseKey aKey)
{
	myCurrentMouseButtonStates[static_cast<unsigned short>(aKey)] = true;
}

void InputListener::MouseReleased(const SB::MouseKey aKey)
{
	myCurrentMouseButtonStates[static_cast<unsigned short>(aKey)] = false;
}
