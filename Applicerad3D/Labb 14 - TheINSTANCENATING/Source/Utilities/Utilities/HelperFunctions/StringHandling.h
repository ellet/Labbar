#pragma once


namespace ENGINE_NAMESPACE
{
	namespace HelperFunction
	{
		void ConvertStringToCharPointer(const std::string & aSource, GrowingArray<char> & aDestionation);
		void ConvertArrayOfStringToCharPointer(const GrowingArray<std::string> & aSource, GrowingArray<GrowingArray<char*>> & aDestionation);
	}
}