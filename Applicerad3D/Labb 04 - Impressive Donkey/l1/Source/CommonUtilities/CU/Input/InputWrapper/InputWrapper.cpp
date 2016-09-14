#include "stdafx.h"

#include "InputWrapper.h"
#include <amp.h>
#include "InputWrapperInputStates.h"
#include "CU/Utility/WindowsFunctions/WindowsFunctions.h"




namespace CommonUtilities
{

	InputWrapper::InputWrapper()
	{
		myInputStates = new InputWrapperInputStates;

		myInputStates->myKeyboardData.resize(256);
		myInputStates->myPreviousKeyboardData.resize(256);
		myImInitialized = false;
	}


	InputWrapper::~InputWrapper()
	{
		myInputStates->myKeyboard->Unacquire();
		myInputStates->myKeyboard->Release();
		myInputStates->myKeyboard = nullptr;

		myInputStates->myMouse->Unacquire();
		myInputStates->myMouse->Release();
		myInputStates->myMouse = nullptr;

		myInputStates->myInputInterface->Release();
		myInputStates->myInputInterface = nullptr;

		delete myInputStates;
		myInputStates = nullptr;
	}


	void InputWrapper::Initialize(/*HINSTANCE aApplicationInstance, HWND aWindow*/)
	{
		HRESULT inputError;
		inputError = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8A, reinterpret_cast<void**>(&myInputStates->myInputInterface), nullptr);
		
		//HWND tempWindowID = ;

		myInputStates->myInputInterface->CreateDevice(GUID_SysKeyboard, &myInputStates->myKeyboard, nullptr);
		myInputStates->myInputInterface->CreateDevice(GUID_SysMouse, &myInputStates->myMouse, nullptr);

		myInputStates->myKeyboard->SetDataFormat(&c_dfDIKeyboard);
		myInputStates->myKeyboard->SetCooperativeLevel(static_cast<HWND>(GetCurrentProcess()), DISCL_BACKGROUND);
		myInputStates->myKeyboard->Acquire();

		myInputStates->myMouse->SetDataFormat(&c_dfDIMouse);
		myInputStates->myMouse->SetCooperativeLevel(static_cast<HWND>(GetCurrentProcess()), DISCL_BACKGROUND);
		myInputStates->myMouse->Acquire();

		myImInitialized = true;
	}

	void InputWrapper::Update()
	{
		if (myImInitialized == false)
		{
			return;
		}

		CU::Vector2f tempPosition = GetMouseWindowPositionNormalizedSpace();

		if (tempPosition.x > 1.f || tempPosition.x < 0.f ||
			tempPosition.y > 1.f || tempPosition.y < 0.f)
		{
			if ((CU::WindowsFunctions::CheckIfWindowFullscreen(static_cast<HWND>(GetCurrentProcess()))) == true)
			{
				CU::Point2ui newPosition(USHORTCAST(tempPosition.x), USHORTCAST(tempPosition.y));

				tempPosition.x = min(1.f, max(tempPosition.x, 0.f));
				tempPosition.y = min(1.f, max(tempPosition.y, 0.f));

				RECT tempWindow;
				GetClientRect(static_cast<HWND>(GetCurrentProcess()), &tempWindow);

				//newPosition.x = newPosition.x * tempWindow.right;
				//newPosition.y = newPosition.y * tempWindow.bottom;
				newPosition.x = USHORTCAST(tempPosition.x) * tempWindow.right -4;
				newPosition.y = USHORTCAST(tempPosition.y) * tempWindow.bottom;

				POINT tempPoint;
				tempPoint.x = newPosition.x;
				tempPoint.y = newPosition.y;
				
				ClientToScreen(static_cast<HWND>(GetCurrentProcess()), &tempPoint);

				SetCursorPosition(tempPoint.x, tempPoint.y);
			}
			else
			{
				if (GetActiveWindow() == static_cast<HWND>(GetCurrentProcess()))
				{
					return;
				}
			}
		}


		myInputStates->myPreviousMouseData = myInputStates->myMouseData;
		myInputStates->myMouse->GetDeviceState(sizeof(DIMOUSESTATE), static_cast<LPVOID>(&myInputStates->myMouseData));

		myInputStates->myPreviousKeyboardData = myInputStates->myKeyboardData;
		myInputStates->myKeyboard->GetDeviceState(sizeof(BYTE) * static_cast<DWORD>(myInputStates->myKeyboardData.size()), static_cast<void*>(&myInputStates->myKeyboardData[0]));
	}

	LONG InputWrapper::GetMouseDeltaX() const
	{
		return myInputStates->myMouseData.lX;
	}

	LONG InputWrapper::GetMouseDeltaY() const
	{
		return myInputStates->myMouseData.lY;
	}

	LONG InputWrapper::GetWheelDelta() const
	{
		return myInputStates->myMouseData.lZ;
	}

	bool InputWrapper::GetMouseButtonDown(enumMouseButtons aButton) const
	{
		return (myInputStates->myMouseData.rgbButtons[static_cast<int>(aButton)] > 0);
	}

	bool InputWrapper::GetMouseButtonReleased(enumMouseButtons aButton) const
	{
		return (myInputStates->myPreviousMouseData.rgbButtons[static_cast<int>(aButton)] > 0) && (!(myInputStates->myMouseData.rgbButtons[static_cast<int>(aButton)] > 0));
	}

	bool InputWrapper::GetMouseButtonPressed(enumMouseButtons aButton) const
	{
		return static_cast<bool>(!(myInputStates->myPreviousMouseData.rgbButtons[static_cast<int>(aButton)] > 0)) && (myInputStates->myMouseData.rgbButtons[static_cast<int>(aButton)] > 0);
	}



	bool InputWrapper::GetKeyDown(int aButton) const
	{
		return myInputStates->myKeyboardData[aButton] > 0;
	}


	bool InputWrapper::GetKeyPressed(int aButton) const
	{
		return (myInputStates->myKeyboardData[aButton] > 0 && myInputStates->myPreviousKeyboardData[aButton] == 0);
	}

	bool InputWrapper::GetKeyReleased(int aButton) const
	{
		return (myInputStates->myKeyboardData[aButton] == 0 && myInputStates->myPreviousKeyboardData[aButton] > 0);
	}

	void InputWrapper::SetCursorPosition(int aXPosition, int aYPosition) const
	{
		SetCursorPos(aXPosition, aYPosition);
	}

	LONG InputWrapper::GetMouseAbsolutePositionX() const
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);
		return tempPoint.x;
	}

	LONG InputWrapper::GetMouseAbsolutePositionY() const
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);
		return tempPoint.y;
	}

	Vector2f InputWrapper::GetMouseWindowPosition() const
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);

		ScreenToClient(static_cast<HWND>(GetCurrentProcess()), &tempPoint);

		/*RECT tempWindow;
		GetClientRect(myWindowID, &tempWindow);*/

		return Vector2f(static_cast<float>(tempPoint.x), static_cast<float>(tempPoint.y));
	}

	Vector2f InputWrapper::GetMouseWindowPositionNormalizedSpace() const
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);

		ScreenToClient(static_cast<HWND>(GetCurrentProcess()), &tempPoint);

		RECT tempWindow;
		GetClientRect(static_cast<HWND>(GetCurrentProcess()), &tempWindow);

		return Vector2f((static_cast<float>(tempPoint.x) / static_cast<float>(tempWindow.right)), (static_cast<float>(tempPoint.y) / static_cast<float>(tempWindow.bottom)));
	}

	 void InputWrapper::ResetInput()
	{
		myInputStates->myKeyboardData.clear();
		myInputStates->myPreviousKeyboardData.clear();

		myInputStates->myKeyboardData.resize(256);
		myInputStates->myPreviousKeyboardData.resize(256);

		/*
		CLEAR MOUSE BUFFERS
		*/
	}

	 bool InputWrapper::GetAnyKeyDown() const
	{
		for (unsigned short iKey = 0; iKey < myInputStates->myKeyboardData.size(); ++iKey)
		{
			if (GetKeyDown(iKey) == true)
			{
				return true;
			}
		}
		return false;
	}

	 bool InputWrapper::GetAnyKeyPressed() const
	{
		for (unsigned short iKey = 0; iKey < myInputStates->myKeyboardData.size(); ++iKey)
		{
			if (GetKeyPressed(iKey) == true)
			{
				return true;
			}
		}
		return false;
	}

	 bool InputWrapper::GetAnyKeyReleased() const
	{
		for (unsigned short iKey = 0; iKey < myInputStates->myKeyboardData.size(); ++iKey)
		{
			if (GetKeyReleased(iKey) == true)
			{
				return true;
			}
		}
		return false;
	}

	bool InputWrapper::GetAnyMouseButtonDown() const
	{
		for (unsigned short iMouseButton = 0; iMouseButton < USHORTCAST(enumMouseButtons::enumLength); ++iMouseButton)
		{
			if (GetMouseButtonDown(static_cast<enumMouseButtons>(iMouseButton)) == true)
			{
				return true;
			}
		}
		return false;
	}

	bool InputWrapper::GetAnyMouseButtonReleased() const
	{
		for (unsigned short iMouseButton = 0; iMouseButton < USHORTCAST(enumMouseButtons::enumLength); ++iMouseButton)
		{
			if (GetMouseButtonReleased(static_cast<enumMouseButtons>(iMouseButton)) == true)
			{
				return true;
			}
		}
		return false;
	}

	bool InputWrapper::GetAnyMouseButtonPressed() const
	{
		for (unsigned short iMouseButton = 0; iMouseButton < USHORTCAST(enumMouseButtons::enumLength); ++iMouseButton)
		{
			if (GetMouseButtonPressed(static_cast<enumMouseButtons>(iMouseButton)) == true)
			{
				return true;
			}
		}
		return false;
	}
}