#include "WindowsFunctions.h"


namespace CommonUtilities
{
	namespace WindowsFunctions
	{
		Vector4f GetWindowSize(HWND aWindowID)
		{
			RECT windowRect;
			GetWindowRect(aWindowID, &windowRect);

			Vector4f temp(static_cast<float>(windowRect.left), static_cast<float>(windowRect.top), static_cast<float>(windowRect.right), static_cast<float>(windowRect.bottom));
			

			return temp;
		}
	}
}