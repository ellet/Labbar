#include "WindowsFunctions.h"


namespace CommonUtilities
{
	namespace WindowsFunctions
	{
		Vector4f GetWindowSize(HWND aWindowID)
		{
			RECT windowRect;
			GetWindowRect(aWindowID, &windowRect);

			Vector4f temp(windowRect.left, windowRect.top, windowRect.right, windowRect.bottom);
			

			return temp;
		}
	}
}