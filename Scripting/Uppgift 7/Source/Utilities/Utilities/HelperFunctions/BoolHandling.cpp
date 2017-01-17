#include "stdafx.h"
#include "StringHandling.h"

namespace SB
{
	namespace HelperFunction
	{

#pragma warning(disable : 4706)
		bool GetAndResetBool(bool &aBool)
		{
			return (aBool ? !(aBool = false) : aBool);
			//does this->
					/*if (myHasChanged == true)
					{
					myHasChanged = false;
					return true;
					}
					return false;*/
		}
#pragma warning(default : 4706)

	}
}