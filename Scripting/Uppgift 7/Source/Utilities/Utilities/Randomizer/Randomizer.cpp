#include "stdafx.h"
#include "Randomizer.h"
#include <time.h>

namespace SB
{


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
		std::uniform_real_distribution<float>::param_type test(aMinValue, aMaxValue);
		myDistribution.param(test);
	}

	void Randomizer::SetSeed(const size_t aSeedValue)
	{
		myRandomGenerator = std::default_random_engine(static_cast<unsigned int>(aSeedValue));
	}

	void Randomizer::SetSeed()
	{
		LARGE_INTEGER pc;
		QueryPerformanceCounter(&pc);
		SetSeed(static_cast<size_t>(pc.QuadPart));
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
}
