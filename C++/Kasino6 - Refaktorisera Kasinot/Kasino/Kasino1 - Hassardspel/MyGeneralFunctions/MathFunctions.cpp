#include "stdafx.h"
#include "MathFunctions.h"

namespace MyFunctions {
namespace Math {

float EnforcePositiveNumber(float aNumberToCheck)
{
	if (aNumberToCheck < 0)
	{
		aNumberToCheck *= -1;
	}
	return aNumberToCheck;
}

int EnforcePositiveNumber(int aNumberToCheck)
{
	if (aNumberToCheck < 0)
	{
		aNumberToCheck *= -1;
	}
	return aNumberToCheck;
}

int SlumpWholeNumber(const int aMax)
{
	int randomNumberHolder = rand() % (aMax);
	randomNumberHolder += 1;
	return randomNumberHolder;
}

int SlumpNumberBetween(const int aMin, const int aMax)
{
	int randomNumberHolder = rand() % (aMax);
	if (randomNumberHolder < (aMax - aMin))
	{
		randomNumberHolder += aMin;
	}

	return randomNumberHolder;
}

bool CheckNumberIfEven(const int aNumberToCheck)
{
	if (aNumberToCheck % 2 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

}
}