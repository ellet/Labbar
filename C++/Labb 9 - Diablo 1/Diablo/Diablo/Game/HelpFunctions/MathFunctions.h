#pragma once
#include <vector>

namespace l1functions
{
	namespace math
	{
		int EnforcePositive(const int aNumberToCheck);

		unsigned int EnforcePositiveSigned(const unsigned int aNumberToCheck);
		
		float EnforcePositive(const float aNumberToCheck);

		unsigned int AddUppVector(const std::vector<unsigned int> & aVectorToAddUp);

		int GetRandomNumber(const int aMax, const int aMin = 0);

		float GetRandomNumber(const float aMax, const float aMin = 0.f);

		bool RandomChanceHappend(const unsigned int aPercentage, bool aCanGoOverHundred = false);

		unsigned int GetRandomNumberSigned(const unsigned int aMax, const unsigned int aMin = 0);
	}
}