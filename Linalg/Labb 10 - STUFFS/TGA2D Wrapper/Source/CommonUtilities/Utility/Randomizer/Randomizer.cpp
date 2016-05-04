#include "Randomizer.h"




Randomizer::Randomizer(float aMinValue /*= 0.f*/, float aMaxValue /*= 1.f*/)
{
	myDistribution = std::uniform_real_distribution<float>(aMinValue, aMaxValue);
}

Randomizer::~Randomizer()
{
}

void Randomizer::SetMinMax(float aMinValue, float aMaxValue)
{
	myDistribution = std::uniform_real_distribution<float>(aMinValue, aMaxValue);
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
