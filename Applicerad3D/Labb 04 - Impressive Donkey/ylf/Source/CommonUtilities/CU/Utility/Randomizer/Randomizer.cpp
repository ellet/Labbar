#include "stdafx.h"
#include "Randomizer.h"
#include <time.h>
#include <chrono>


Randomizer::Randomizer(float aMinValue /*= 0.f*/, float aMaxValue /*= 1.f*/)
{
	myDistribution = std::uniform_real_distribution<float>(aMinValue, aMaxValue);
	SetSeed();
}

Randomizer::~Randomizer()
{
}

void Randomizer::SetMinMax(float aMinValue, float aMaxValue)
{
	std::uniform_real_distribution<float>::param_type minMax(aMinValue, aMaxValue);
	myDistribution.param(minMax);
}

void Randomizer::SetSeed(const size_t aSeedValue)
{
	myRandomGenerator = std::default_random_engine(static_cast<unsigned int>(aSeedValue));
}

void Randomizer::SetSeed()
{
	SetSeed(time(0));
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
