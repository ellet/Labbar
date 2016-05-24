#include "stdafx.h"
#include "Randomizer.h"



Randomizer::Randomizer(unsigned int aSeed /*= 3*/,float aMinValue /*= 0.f*/, float aMaxValue /*= 1.f*/)
{
	myDistribution = std::uniform_real_distribution<float>(aMinValue, aMaxValue);
	myRandomGenerator = std::default_random_engine(aSeed);
}

Randomizer::~Randomizer()
{
}

void Randomizer::SetMinMax(float aMinValue, float aMaxValue)
{
	std::uniform_real_distribution<float>::param_type test(aMinValue, aMaxValue);
	myDistribution.param(test);
}

float Randomizer::GetRandomValue()
{
	return myDistribution(myRandomGenerator);
}

float Randomizer::GetRandomValue(float aMinValue, float aMaxValue)
{
	SetMinMax(aMinValue, aMaxValue);
	return GetRandomValue();
}
