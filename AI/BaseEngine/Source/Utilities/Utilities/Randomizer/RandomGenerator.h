#include <Windows.h>
#include <time.h>

namespace RandomGenerator
{
	//Initialize random seed
	inline void Init()
	{
		srand(static_cast<unsigned int>(time(0)));
	}

	//Initialize random seed to aSeed
	inline void Init(const unsigned int aSeed)
	{
		srand(aSeed);
	}

	//Returns a random float value between aMinValue and aMaxValue.
	inline float RandomFloat(const float aMinValue = 0.f, const float aMaxValue = 1.f)
	{
		return aMinValue + ((aMaxValue - aMinValue) * static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
	}

	//Returns a random number between aMinValue and aMaxValue.
	inline int RandomRange(const int aMinValue, const int aMaxValue)
	{
		int range = aMaxValue - aMinValue;
		int result = (rand() % (range + 1)) + aMinValue;

		return result;
	}

	//Returns a random number between aMinValue and aMaxValue.
	inline unsigned short RandomRange(const unsigned short aMinValue, const unsigned short aMaxValue)
	{
		unsigned short range = aMaxValue - aMinValue;
		unsigned short result = (rand() % (range + 1)) + aMinValue;

		return result;
	}

	//Returns true if a percentage roll (1-100), modified by aRollModifier, is met.
	// * aChance = Percentage chance to return true - a value between 1-100
	// * aRollModifier = Modifier to the percentage roll
	inline bool IsPercentageChanceMet(unsigned int aChance, int aRollModifier = 0)
	{
		int roll = RandomRange(1, 100);
		int sum = roll + aRollModifier;
		if (sum < 1)
		{
			sum = 1;
		}
		else if (sum > 100)
		{
			sum = 100;
		}

		if (sum <= static_cast<int>(aChance))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

} namespace Random = RandomGenerator; namespace RandomGen = RandomGenerator;