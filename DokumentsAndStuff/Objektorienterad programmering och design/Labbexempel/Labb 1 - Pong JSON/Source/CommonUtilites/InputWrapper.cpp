#include "stdafx.h"
#include "InputWrapper.h"
#include "Macros.h"
#include <assert.h>

namespace Input
{
	InputWrapper::InputWrapper()
	{
		myIsInitialized = false;

		// Set all keys to unpressed by default. ZeroMemory is a macro that 
		ZeroMemory(&myPreviousKeyState, sizeof(BYTE) * 256);
		ZeroMemory(&myKeyState, sizeof(BYTE) * 256);
		ZeroMemory(&myMouseState, sizeof(myMouseState));

		myWindowWidth = 0;
		myWindowHeight = 0;

		SetMouseSpeed(1);
		SetMousePosition(0, 0);
	}


	InputWrapper::~InputWrapper()
	{
		// Objects deletes all their allocated resources and clean up 
		myDirectInputMouse->Unacquire();
		myDirectInputKeyboard->Unacquire();
		myDirectInputMouse->Release();
		myDirectInputKeyboard->Release();
		myDirectInput->Release();
	}


	void InputWrapper::Init(HINSTANCE aHInstance, HWND aHWND, int aWindowWidth, int aWindowHeight)
	{
		SetMousePosition(aWindowWidth / 2, aWindowHeight / 2);

		HRESULT result;

		// Initialize Direct Input
		result = DirectInput8Create(aHInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&myDirectInput), nullptr);
		assert(SUCCEEDED(result) && "Failed to initialize direct input");


		// Initialize keyboard and mouse
		result = myDirectInput->CreateDevice(GUID_SysKeyboard, &myDirectInputKeyboard, nullptr);
		assert(SUCCEEDED(result) && "Failed to initialize keyboard.");

		result = myDirectInput->CreateDevice(GUID_SysMouse, &myDirectInputMouse, nullptr);
		assert(SUCCEEDED(result) && "Failed to initialize mouse.");


		// Set type format that the devices should return
		myDirectInputKeyboard->SetDataFormat(&c_dfDIKeyboard);
		myDirectInputMouse->SetDataFormat(&c_dfDIMouse);


		// Set how this program will use and share the input with other applications
		result = myDirectInputKeyboard->SetCooperativeLevel(aHWND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		assert(SUCCEEDED(result) && "Failed to set cooperative level on keyboard.");

		result = myDirectInputMouse->SetCooperativeLevel(aHWND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		assert(SUCCEEDED(result) && "Failed to set cooperative level on mouse.");
		

		myWindowWidth = aWindowWidth;
		myWindowHeight = aWindowHeight;

		myIsInitialized = true;

	}


	bool InputWrapper::GetKeyDown(unsigned char aKey) const
	{
		assert(aKey < 256 && "Unknown Key!");
		return IsPressed(myKeyState[aKey]) == true;
	}


	bool InputWrapper::GetKeyPressed(unsigned char aKey) const
	{
		assert(aKey < 256 && "Unknown Key!");
		return IsPressed(myKeyState[aKey]) == true && IsPressed(myPreviousKeyState[aKey]) == false;
	}


	bool InputWrapper::GetKeyReleased(unsigned char aKey) const
	{
		assert(aKey < 256 && "Unknown Key!");
		return IsPressed(myKeyState[aKey]) == false && IsPressed(myPreviousKeyState[aKey]) == true;
	}


	bool InputWrapper::GetMouseButtonDown(const eMouseButtons aMouseButton) const
	{
		return IsPressed(myMouseState.rgbButtons[static_cast<int>(aMouseButton)]) == true;
	}


	bool InputWrapper::GetMouseButtonPressed(const eMouseButtons aMouseButton) const
	{
		return IsPressed(myMouseState.rgbButtons[static_cast<int>(aMouseButton)]) == true &&
			IsPressed(myPreviousMouseState.rgbButtons[static_cast<int>(aMouseButton)]) == false;
	}


	bool InputWrapper::GetMouseButtonReleased(const eMouseButtons aMouseButton) const
	{
		return IsPressed(myMouseState.rgbButtons[static_cast<int>(aMouseButton)]) == false && 
			IsPressed(myPreviousMouseState.rgbButtons[static_cast<int>(aMouseButton)]) == true;
	}


	Position InputWrapper::GetMousePosition() const
	{
		return myMousePosition;
	}


	Position InputWrapper::GetMouseDeltaPosition() const
	{
		Position position;
		position.myX = myMouseState.lX;
		position.myY = myMouseState.lY;
		return position;
	}


	LONG InputWrapper::GetMouseScroll() const
	{
		return myMouseState.lZ;
	}


	Position InputWrapper::GetWindowsMousePosition() const
	{
		POINT position;
		GetCursorPos(&position);

		Position returnPosition;
		returnPosition.myX = position.x;
		returnPosition.myY = position.y;

		return returnPosition;
	}


	void InputWrapper::UpdateMousePosition()
	{
		myMousePosition.myX += static_cast<LONG>(myMouseState.lX * myMouseSpeed);
		myMousePosition.myY += static_cast<LONG>(myMouseState.lY * myMouseSpeed);

		myMousePosition.myX = RANGE(myMousePosition.myX, 1, myWindowWidth);
		myMousePosition.myY = RANGE(myMousePosition.myY, 1, myWindowHeight);
	}


	void InputWrapper::SetMouseSpeed(const float aMouseSpeed)
	{
		myMouseSpeed = aMouseSpeed;
		if (myMouseSpeed < 0.01f)
		{
			myMouseSpeed = 0.01f;
		}
	}


	void InputWrapper::SetMousePosition(const int aX, const int aY)
	{
		myMousePosition.myX = aX;
		myMousePosition.myY = aY;
	}

	void InputWrapper::Update()
	{
		// Don't try to update if we haven't initialized direct input and devices
		if (myIsInitialized == false)
		{
			return;
		}

		SavePreviousInputStates();

		// Aquire mouse and keyboard input
		myDirectInputMouse->Acquire();
		myDirectInputKeyboard->Acquire();

		// Get mouse state
		myDirectInputMouse->GetDeviceState(sizeof(DIMOUSESTATE), static_cast<LPVOID>(&myMouseState));

		// Get keyboard state
		myDirectInputKeyboard->GetDeviceState(256, static_cast<LPVOID>(myKeyState));

		UpdateMousePosition();
	}


	void InputWrapper::SavePreviousInputStates()
	{
		for (int i = 0; i < 255; ++i)
		{
			myPreviousKeyState[i] = myKeyState[i];
		}

		myPreviousMouseState = myMouseState;
	}


	bool InputWrapper::IsPressed(BYTE aValue) const
	{
		return ( (aValue & 0x80) > 0 );
	}
}
