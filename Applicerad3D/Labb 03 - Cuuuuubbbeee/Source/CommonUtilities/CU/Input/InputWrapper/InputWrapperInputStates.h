#pragma once

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include <dinput.h>
#include <vector>

struct InputWrapperInputStates
{
	LPDIRECTINPUT8 myInputInterface;
	LPDIRECTINPUTDEVICE8 myKeyboard;
	LPDIRECTINPUTDEVICE8 myMouse;

	std::vector<BYTE> myKeyboardData;
	std::vector<BYTE> myPreviousKeyboardData;

	DIMOUSESTATE myMouseData;
	DIMOUSESTATE myPreviousMouseData;
};