#include "stdafx.h"
#include "MathFunctions.h"
#include <random>
#include <cmath>
#include "consolefunctions.h"

namespace l1functions
{
	namespace math
	{

		int l1functions::math::EnforcePositive(const int aNumberToCheck)
		{
			return static_cast<int>(EnforcePositive(static_cast<float>(aNumberToCheck)));
		}

		unsigned int EnforcePositiveSigned(const unsigned int aNumberToCheck)
		{
			if (aNumberToCheck > 0)
			{
				return aNumberToCheck;
			}
			else
			{
				return aNumberToCheck * -1;
			}
		}

		float l1functions::math::EnforcePositive(const float aNumberToCheck)
		{
			if (aNumberToCheck > 0)
			{
				return aNumberToCheck;
			}
			else
			{
				return aNumberToCheck * -1;
			}
		}

		unsigned int AddUppVector(const std::vector<unsigned int> & aVectorToAddUp)
		{
			unsigned int sumHolder = 0;
			for (unsigned int aNumber = 0; aNumber < aVectorToAddUp.size(); ++aNumber)
			{
				sumHolder += aVectorToAddUp[aNumber];
			}
			return sumHolder;
		}
		
		int GetRandomNumber(const int aMax, const int aMin)
		{
			if (aMax > aMin && aMax > 0)
			{
				return (std::rand() % (aMax - aMin)) + aMin;


			}
			else
			{
				l1functions::console::PrintErrorToConsole("Random Number Max is either negative or smaller or equal to min");
				return 0;
			}
		}

		float GetRandomNumber(const float aMax, const float aMin)
		{
			if (aMax > aMin && aMax > 0)
			{
				float randomNumber = fmod(static_cast<float>(std::rand()), aMax - aMin) + aMin;


				return randomNumber;
			}
			else
			{
				l1functions::console::PrintErrorToConsole("Random Number Max is either negative or smaller or equal to min");
			}
			return 0.f;
		}

		bool RandomChanceHappend(const unsigned int aPercentage, bool aCanGoOverHundered)
		{
			if (aPercentage < 100)
			{
				const unsigned int rollChans = GetRandomNumber(100);

				if (rollChans < aPercentage)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (aCanGoOverHundered == true)
				{
					return true;
				}
				else
				{
					l1functions::console::PrintErrorToConsole("Percentage is too high");
					return false;
				}
			}
		}




		unsigned int GetRandomNumberSigned(const unsigned int aMax, const unsigned int aMin)
		{
			unsigned int randomNumber = std::rand() % EnforcePositiveSigned(aMax);

			if (randomNumber < EnforcePositiveSigned(aMax - aMin))
			{
				randomNumber += aMin;
			}

			return randomNumber;
		}
	}
}