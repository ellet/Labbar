#include "stdafx.h"
#include "SwapFunctions.h"

void CommonUtilities::Swap(unsigned int& aValue,unsigned int& aValue2)
{
	unsigned int firstValue = aValue;
	aValue = aValue2;
	aValue2 = firstValue;
}

void CommonUtilities::Swap(bool& aValue,bool& aValue2)
{
	bool firstValue = aValue;
	aValue = aValue2;
	aValue2 = firstValue;
}