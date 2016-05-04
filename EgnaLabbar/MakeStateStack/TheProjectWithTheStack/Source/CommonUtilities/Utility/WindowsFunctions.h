#pragma once

#include <windows.h>
#include "../Vectors/Vector.h"


namespace CommonUtilities
{
	namespace WindowsFunctions
	{
		Vector4f GetWindowSize(HWND aWindowID);
	}
}