#pragma once
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <dinput.h>
#include <vector>
#include "../Utility/WindowsFunctions.h"
#include "../DLDebug/DL_Debug.h"
//#include "../Vectors/vector2.h"
//#include "../Vectors/vector4.h"


namespace CommonUtilities
{

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
		static void Create();
		static void Destroy();

		static void Initialize(HINSTANCE aApplicationInstance, HWND aWindow);

		static void Update();

		inline static LONG GetMouseDeltaX();
		inline static LONG GetMouseDeltaY();
		inline static LONG GetWheelDelta();

		inline static bool GetMouseButtonDown(enumMouseButtons aButton);
		inline static bool GetMouseButtonReleased(enumMouseButtons aButton);
		inline static bool GetMouseButtonPressed(enumMouseButtons aButton);

		inline static bool GetKeyDown(int aButton);
		inline static bool GetKeyPressed(int aButton);
		inline static bool GetKeyReleased(int aButton);

		inline static void SetCursorPosition(int aXPosition, int aYPosition);

		inline static LONG GetMouseAbsolutePositionX();
		inline static LONG GetMouseAbsolutePositionY();

		inline static Vector2f GetMouseWindowPosition();

		inline static Vector2f GetMouseWindowPositionNormalizedSpace();


	private:
		InputWrapper();
		~InputWrapper();

		void InternalInitialize(HINSTANCE aApplicationInstance, HWND aWindow);

		void InternalUpdate();

		inline LONG InternalGetMouseDeltaX();
		inline LONG InternalGetMouseDeltaY();
		inline LONG InternalGetWheelDelta();

		inline bool InternalGetMouseButtonDown(enumMouseButtons aButton);
		inline bool InternalGetMouseButtonReleased(enumMouseButtons aButton);
		inline bool InternalGetMouseButtonPressed(enumMouseButtons aButton);

		inline bool InternalGetKeyDown(int aButton);
		inline bool InternalGetKeyPressed(int aButton);
		inline bool InternalGetKeyReleased(int aButton);

		inline void InternalSetCursorPosition(int aXPosition, int aYPosition);

		inline LONG InternalGetMouseAbsolutePositionX();
		inline LONG InternalGetMouseAbsolutePositionY();

		inline Vector2f InternalGetMouseWindowPosition();

		inline Vector2f InternalGetMouseWindowPositionNormalizedSpace();


		static InputWrapper * ourInstance;
		inline static InputWrapper & GetInstance();

		LPDIRECTINPUT8 myInputInterface;
		LPDIRECTINPUTDEVICE8 myKeyboard;
		LPDIRECTINPUTDEVICE8 myMouse;

		std::vector<BYTE> myKeyboardData;
		std::vector<BYTE> myPreviousKeyboardData;

		DIMOUSESTATE myMouseData;
		DIMOUSESTATE myPreviousMouseData;

		HWND myWindowID;
		bool myImInitialized;
	};

	inline InputWrapper & InputWrapper::GetInstance()
	{
		DL_ASSERT(ourInstance != nullptr, "InputWrapper Instance is nullptr");
		return (*ourInstance);
	}

	inline  LONG InputWrapper::GetMouseDeltaX()
	{
		return GetInstance().InternalGetMouseDeltaX();
	}

	inline LONG InputWrapper::GetMouseDeltaY()
	{
		return GetInstance().InternalGetMouseDeltaY();
	}


	inline LONG InputWrapper::GetWheelDelta()
	{
		return GetInstance().InternalGetWheelDelta();
	}

	inline bool InputWrapper::GetMouseButtonDown(enumMouseButtons aButton)
	{
		return GetInstance().InternalGetMouseButtonDown(aButton);
	}

	inline bool InputWrapper::GetMouseButtonReleased(enumMouseButtons aButton)
	{
		return GetInstance().InternalGetMouseButtonReleased(aButton);
	}


	inline bool InputWrapper::GetMouseButtonPressed(enumMouseButtons aButton)
	{
		return GetInstance().InternalGetMouseButtonPressed(aButton);
	}

	inline bool InputWrapper::GetKeyDown(int aButton)
	{
		return GetInstance().InternalGetKeyDown(aButton);
	}

	inline bool InputWrapper::GetKeyPressed(int aButton)
	{
		return GetInstance().InternalGetKeyPressed(aButton);
	}

	inline bool InputWrapper::GetKeyReleased(int aButton)
	{
		return GetInstance().InternalGetKeyReleased(aButton);
	}

	inline void InputWrapper::SetCursorPosition(int aXPosition, int aYPosition)
	{
		return GetInstance().InternalSetCursorPosition(aXPosition, aYPosition);
	}

	inline LONG InputWrapper::GetMouseAbsolutePositionX()
	{
		return GetInstance().InternalGetMouseAbsolutePositionX();
	}

	inline LONG InputWrapper::GetMouseAbsolutePositionY()
	{
		return GetInstance().InternalGetMouseAbsolutePositionY();
	}

	inline Vector2f InputWrapper::GetMouseWindowPosition()
	{
		return GetInstance().InternalGetMouseWindowPosition();
	}

	inline Vector2f InputWrapper::GetMouseWindowPositionNormalizedSpace()
	{
		return GetInstance().InternalGetMouseWindowPositionNormalizedSpace();
	}

	LONG InputWrapper::InternalGetMouseDeltaX()
	{
		return myMouseData.lX;
	}

	LONG InputWrapper::InternalGetMouseDeltaY()
	{
		return myMouseData.lY;
	}

	LONG InputWrapper::InternalGetWheelDelta()
	{
		return myMouseData.lZ;
	}

	bool InputWrapper::InternalGetMouseButtonDown(enumMouseButtons aButton)
	{
		return (myMouseData.rgbButtons[static_cast<int>(aButton)] > 0);
	}

	bool InputWrapper::InternalGetMouseButtonReleased(enumMouseButtons aButton)
	{
		return (myPreviousMouseData.rgbButtons[static_cast<int>(aButton)] > 0) && (!(myMouseData.rgbButtons[static_cast<int>(aButton)] > 0));
	}

	bool InputWrapper::InternalGetMouseButtonPressed(enumMouseButtons aButton)
	{
		return static_cast<bool>(!(myPreviousMouseData.rgbButtons[static_cast<int>(aButton)] > 0)) && (myMouseData.rgbButtons[static_cast<int>(aButton)] > 0);
	}



	bool InputWrapper::InternalGetKeyDown(int aButton)
	{
		return myKeyboardData[aButton] > 0;
	}


	bool InputWrapper::InternalGetKeyPressed(int aButton)
	{
		return (myKeyboardData[aButton] > 0 && myPreviousKeyboardData[aButton] == 0);
	}

	bool InputWrapper::InternalGetKeyReleased(int aButton)
	{
		return (myKeyboardData[aButton] == 0 && myPreviousKeyboardData[aButton] > 0);
	}

	void InputWrapper::InternalSetCursorPosition(int aXPosition, int aYPosition)
	{
		SetCursorPos(aXPosition, aYPosition);
	}

	LONG InputWrapper::InternalGetMouseAbsolutePositionX()
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);
		return tempPoint.x;
	}

	LONG InputWrapper::InternalGetMouseAbsolutePositionY()
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);
		return tempPoint.y;
	}

	inline Vector2f InputWrapper::InternalGetMouseWindowPosition()
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);

		ScreenToClient(myWindowID, &tempPoint);

		/*RECT tempWindow;
		GetClientRect(myWindowID, &tempWindow);*/

		return Vector2f(static_cast<float>(tempPoint.x), static_cast<float>(tempPoint.y));
	}

	inline Vector2f InputWrapper::InternalGetMouseWindowPositionNormalizedSpace()
	{
		POINT tempPoint;
		GetCursorPos(&tempPoint);

		ScreenToClient(myWindowID, &tempPoint);

		RECT tempWindow;
		GetClientRect(myWindowID, &tempWindow);

		return Vector2f((static_cast<float>(tempPoint.x) / static_cast<float>(tempWindow.right)), (static_cast<float>(tempPoint.y) / static_cast<float>(tempWindow.bottom)));
	}

}