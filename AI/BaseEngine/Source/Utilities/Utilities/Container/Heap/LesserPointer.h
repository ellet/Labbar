#pragma once
namespace SB
{
	class LesserPointer
	{
	public:

		template <typename T>
		bool operator()(const T &aFirst, const T &aSecond)
		{
			if (*aFirst < *aSecond)
			{
				return true;
			}
			return false;
		}
	};


};