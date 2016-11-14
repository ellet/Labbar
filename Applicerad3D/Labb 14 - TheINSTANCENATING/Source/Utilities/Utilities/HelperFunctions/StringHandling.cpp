#include "stdafx.h"
#include "StringHandling.h"

namespace ENGINE_NAMESPACE
{
	namespace HelperFunction
	{
		void ConvertStringToCharPointer(const std::string & aSource, GrowingArray<char> & aDestionation)
		{
			aDestionation.Resize(static_cast<unsigned short>( aSource.length()));

			if (aSource.length() > 0)
			{
				memcpy(&aDestionation[0], aSource.c_str(), aSource.length());
			}
			aDestionation.Add('\0');
		}

		void ConvertArrayOfStringToCharPointer(const GrowingArray<std::string> & aSource, GrowingArray<GrowingArray<char*>> & aDestionation)
		{
			aDestionation.Resize(aSource.Size());

			for (unsigned short iString = 0; iString < aSource.Size(); ++iString)
			{
				GrowingArray<char> tempArray;
				ConvertStringToCharPointer(aSource[iString], tempArray);

				aDestionation[iString].Resize(tempArray.Size());

				char* tempbajs = aDestionation[iString][0];
				const char* sourceBajs = &tempArray[0];
				const size_t countBajs = tempArray.Size();

				memcpy(tempbajs, sourceBajs, countBajs);
			}
		}

	}
}