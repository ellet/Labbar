#include "Randomizer.h"
#include <ctime>



Randomizer::Randomizer(float aMinValue /*= 0.f*/, float aMaxValue /*= 1.f*/)
{
	myDistribution = std::uniform_real_distribution<float>(aMinValue, aMaxValue);
	myRandomGenerator.seed(std::time(nullptr));
	//myRandomGenerator.seed(3);
}

Randomizer::~Randomizer()
{
}

void Randomizer::SetMinMax(float aMinValue, float aMaxValue)
{
	std::uniform_real_distribution<float>::param_type minmaxRange(aMinValue, aMaxValue);
	myDistribution.param(minmaxRange);
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
