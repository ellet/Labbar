#pragma once



#include <vector>
#include "CU/NameSpaceAliases.h"
#include "CU/Input/InputWrapper/MouseButtonsEnum.h"
#include "CU/Utility/CommonCasts.h"

struct InputWrapperInputStates;

namespace CommonUtilities
{
	class InputWrapper
	{
	public:
		InputWrapper();
		~InputWrapper();

		void Initialize(/*HINSTANCE aApplicationInstance, HWND aWindow*/);

		void Update();

		LONG GetMouseDeltaX() const;
		LONG GetMouseDeltaY() const;
		LONG GetWheelDelta() const;

		bool GetMouseButtonDown(enumMouseButtons aButton) const;
		bool GetMouseButtonReleased(enumMouseButtons aButton) const;
		bool GetMouseButtonPressed(enumMouseButtons aButton) const;

		bool GetAnyMouseButtonDown() const;
		bool GetAnyMouseButtonReleased() const;
		bool GetAnyMouseButtonPressed() const;

		bool GetKeyDown(int aButton) const;
		bool GetKeyPressed(int aButton) const;
		bool GetKeyReleased(int aButton) const;

		bool GetAnyKeyDown() const;
		bool GetAnyKeyPressed() const;
		bool GetAnyKeyReleased() const;


		void SetCursorPosition(int aXPosition, int aYPosition) const;

		LONG GetMouseAbsolutePositionX() const;
		LONG GetMouseAbsolutePositionY() const;

		Vector2f GetMouseWindowPosition() const;

		Vector2f GetMouseWindowPositionNormalizedSpace() const;

		void ResetInput();

	private:
		InputWrapperInputStates * myInputStates;

		//HWND myWindowID;
		bool myImInitialized;
	};
}