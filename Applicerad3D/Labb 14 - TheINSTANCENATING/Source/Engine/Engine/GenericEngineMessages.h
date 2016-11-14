#pragma once
#include "Engine/Window/Cursor/Cursor.h"

namespace ENGINE_NAMESPACE
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

}
