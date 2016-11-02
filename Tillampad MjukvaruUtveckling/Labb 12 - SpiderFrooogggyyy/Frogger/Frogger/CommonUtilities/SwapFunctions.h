#ifndef SWAP_FUNTIONS_HEADER
#define SWAP_FUNTIONS_HEADER

namespace CommonUtilities
{

	void Swap(unsigned int& aValue,unsigned int& aValue2);

	template <typename TYPE>
	void SwapNum(TYPE& aValue, TYPE& aSecValue)
	{
		TYPE firstValue = aValue;
		aValue = aSecValue;
		aSecValue = firstValue;
	};

	void Swap(bool& aValue,bool& aValue2);
}

#endif