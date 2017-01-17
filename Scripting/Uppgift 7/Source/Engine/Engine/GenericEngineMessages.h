#pragma once
#include "Engine/Window/Cursor/Cursor.h"

namespace SB
{
	struct CloseGameMessage
	{
	};

	struct EndOfFrameMessage
	{
	};

	struct ShowCursorMessage
	{
		ShowCursorMessage(bool aShouldShow)
		{
			myShouldShow = aShouldShow;
		}

		bool myShouldShow;
	};

	struct ChangeCursorMessage
	{
		ChangeCursorMessage(eCursorState aState)
		{
			myState = aState;
		}
		eCursorState myState;
	};

	struct ConfineMouseMessage
	{
		ConfineMouseMessage(const bool aConfinedStateFlag) : myConfinedFlag(aConfinedStateFlag)
		{}
		
		bool myConfinedFlag;
	};
	
	struct WindowSizeChangedMessage
	{
		WindowSizeChangedMessage(const int aWidth, const int aHeight)
		{
			myWidth = aWidth;
			myHeight = aHeight;
		}

		int myWidth;
		int myHeight;
	};

}
