#pragma once
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <dinput.h>
#include <vector>

enum class enumMouseButtons
{
	eRight,
	eLeft,
	eMiddle,
	enumLength
};

class InputWrapper
{
public:
	InputWrapper();
	~InputWrapper();

	void Initialize(HINSTANCE aApplicationInstance, HWND aWindow);

	void Update();

	inline LONG GetMouseDeltaX();
	inline LONG GetMouseDeltaY();
	inline LONG GetWheelDelta();

	inline bool GetMouseButtonDown(enumMouseButtons aButton);
	inline bool GetMouseButtonReleased(enumMouseButtons aButton);
	inline bool GetMouseButtonPressed(enumMouseButtons aButton);

	inline bool GetKeyDown(int aButton);
	inline bool GetKeyPressed(int aButton);
	inline bool GetKeyReleased(int aButton);

	inline void SetCursorPosition(int aXPosition, int aYPosition);

	inline LONG GetMouseAbsolutePositionX();
	inline LONG GetMouseAbsolutePositionY();

private:

	LPDIRECTINPUT8 myInputInterface;
	LPDIRECTINPUTDEVICE8 myKeyboard;
	LPDIRECTINPUTDEVICE8 myMouse;
	
	std::vector<BYTE> myKeyboardData;
	std::vector<BYTE> myPreviousKeyboardData;

	DIMOUSESTATE myMouseData;
	DIMOUSESTATE myPreviousMouseData;
};


LONG InputWrapper::GetMouseDeltaX()
{
	return myMouseData.lX;
}

LONG InputWrapper::GetMouseDeltaY()
{
	return myMouseData.lY;
}

LONG InputWrapper::GetWheelDelta()
{
	return myMouseData.lZ;
}

bool InputWrapper::GetMouseButtonDown(enumMouseButtons aButton)
{
	return (myMouseData.rgbButtons[static_cast<int>(aButton)] > 0);
}

bool InputWrapper::GetMouseButtonReleased(enumMouseButtons aButton)
{
	return (myPreviousMouseData.rgbButtons[static_cast<int>(aButton)] > 0) && (!(myMouseData.rgbButtons[static_cast<int>(aButton)] > 0));
}

bool InputWrapper::GetMouseButtonPressed(enumMouseButtons aButton)
{
	return static_cast<bool>(!(myPreviousMouseData.rgbButtons[static_cast<int>(aButton)] > 0)) && (myMouseData.rgbButtons[static_cast<int>(aButton)] > 0);
}



bool InputWrapper::GetKeyDown(int aButton)
{
	return myKeyboardData[aButton] > 0;
}


bool InputWrapper::GetKeyPressed(int aButton)
{
	return (myKeyboardData[aButton] > 0 && myPreviousKeyboardData[aButton] == 0);
}

bool InputWrapper::GetKeyReleased(int aButton)
{
	return (myKeyboardData[aButton] == 0 && myPreviousKeyboardData[aButton] > 0);
}

void InputWrapper::SetCursorPosition(int aXPosition, int aYPosition)
{
	SetCursorPos(aXPosition, aYPosition);
}

LONG InputWrapper::GetMouseAbsolutePositionX()
{
	POINT tempPoint;
	GetCursorPos(&tempPoint);
	return tempPoint.x;
}

LONG InputWrapper::GetMouseAbsolutePositionY()
{
	POINT tempPoint;
	GetCursorPos(&tempPoint);
	return tempPoint.y;
}