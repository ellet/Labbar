#include "stdafx.h"
#include "TestClassAddingNumbers.h"


TestClassAddingNumbers::TestClassAddingNumbers()
{
	myTestNumber = 0;
}


TestClassAddingNumbers::~TestClassAddingNumbers()
{
}

void TestClassAddingNumbers::IncreaseByOne()
{
	++myTestNumber;
}

void TestClassAddingNumbers::IncreaseByNumber(const int aNumber)
{
	myTestNumber += aNumber;
}