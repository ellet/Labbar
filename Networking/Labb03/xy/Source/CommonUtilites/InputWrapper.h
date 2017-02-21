#ifndef INPUTWRAPPER_H
#define INPUTWRAPPER_H
#define DIRECTINPUT_VERSION 0x0800
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include <dinput.h>

namespace Input
{
	struct Position
	{
		LONG myX;
		LONG myY;
	};

	enum class eMouseButtons
	{
		eLeftMouseButton,
		eRightMouseButton,
		eMiddleMouseButton
	};

	class InputWrapper
	{
	public:
		InputWrapper();
		~InputWrapper();

		bool GetKeyPressed(unsigned char aKey) const;
		bool GetKeyReleased(unsigned char aKey) const;
		bool GetKeyDown(unsigned char aKey) const;

		bool GetMouseButtonDown(const eMouseButtons aMouseButton) const;
		bool GetMouseButtonPressed(const eMouseButtons aMouseButton) const;
		bool GetMouseButtonReleased(const eMouseButtons aMouseButton) const;

		Position GetLocalWindowMousePosition() const;
		Position GetWindowsMousePosition() const;
		Position GetMousePosition() const;
		Position GetMouseDeltaPosition() const;
		LONG GetMouseScroll() const;
		void SetMouseSpeed(const float aMouseSpeed);
		void SetMousePosition(const int aX, const int aY);

		void Init(HINSTANCE aHInstance, HWND aHWND, int aWindowWidth, int aWindowHeight);
		void Update();

		inline bool IsInitialized() const;

	private:
		LPDIRECTINPUT8 myDirectInput; // Pointer to Direct Input 
		LPDIRECTINPUTDEVICE8 myDirectInputKeyboard; // Pointer to keyboard device
		LPDIRECTINPUTDEVICE8 myDirectInputMouse; // Pointer to mouse device
	
		DIMOUSESTATE myMouseState; // A struct with mouse delta positions and button states
		DIMOUSESTATE myPreviousMouseState; // State of mouse last frame

		BYTE myKeyState[256]; // State of each key
		BYTE myPreviousKeyState[256]; // State of each key from last update

		void SavePreviousInputStates();
		bool IsPressed(BYTE aValue) const;

		void UpdateMousePosition();

		bool myIsInitialized;
		Position myMousePosition;

		int myWindowWidth;
		int myWindowHeight;

		float myMouseSpeed;

	};

	bool InputWrapper::IsInitialized() const
	{
		return myIsInitialized;
	}
}
#endif