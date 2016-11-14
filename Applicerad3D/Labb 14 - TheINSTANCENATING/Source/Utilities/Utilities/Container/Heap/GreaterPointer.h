#pragma once
#pragma message( "Compiled " __FILE__ " on " __DATE__ " at " __TIME__ ) 

namespace ENGINE_NAMESPACE
{
	class GreaterPointer
	{
	public:

		template <typename T>
		bool operator()(const T &aFirst, const T &aSecond)
		{
			if (*aFirst > *aSecond)
			{
				return true;
			}
			return false;
		}
	};
};