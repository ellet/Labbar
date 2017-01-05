#pragma once

namespace SB
{

	struct AnyKeyDownMessage
	{
		AnyKeyDownMessage(KeyboardKey aKey)
		{
			key = aKey;
		}

		KeyboardKey key;
	};

	struct AnyKeyRepeatMessage
	{
		AnyKeyRepeatMessage(KeyboardKey aKey, int aRepeatCount)
		{
			key = aKey;
			repeatCount = aRepeatCount;
			isFirstRepeat = repeatCount == 0;
		}

		KeyboardKey key;
		int repeatCount;
		bool isFirstRepeat;
	};

	struct AnyKeyUpMessage
	{
		AnyKeyUpMessage(KeyboardKey aKey)
		{
			key = aKey;
		}

		KeyboardKey key;
	};
}