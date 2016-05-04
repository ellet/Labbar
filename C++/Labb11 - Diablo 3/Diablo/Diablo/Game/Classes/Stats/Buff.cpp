#include "stdafx.h"
#include "Buff.h"
#include "../../HelpFunctions/MathFunctions.h"

Buff::Buff()
{
	myValue = 0;
	myBuffType = enumItemTypes::enumLength;

	myFirstRound = 0;
	myTimer = 0;
}


Buff::~Buff()
{
}

void Buff::Initialize(unsigned int aValue, enumItemTypes aBuffType, unsigned int aTimer, enumStatTypes aStatType, enumVitalTypes aVitalType)
{
	myValue = aValue;
	myBuffType = aBuffType;
	myStatType = aStatType;
	myVitalType = aVitalType;

	myTimer = aTimer;
}

unsigned int Buff::GetBuffValue() const
{
	return myValue;
}

enumItemTypes Buff::GetBuffType() const
{
	return myBuffType;
}

enumStatTypes Buff::GetStatType() const
{
	return myStatType;
}

enumVitalTypes Buff::GetVitalType() const
{
	return myVitalType;
}

unsigned int Buff::GetSumOfBuffVector(const std::vector<Buff>& aBuffVectorToAddUp)
{
	std::vector<unsigned int> tempIntVector;
	BuildIntVectorFromBuff(aBuffVectorToAddUp, tempIntVector);
	return l1functions::math::AddUppVector(tempIntVector);
}

void Buff::BuildIntVectorFromBuff(const std::vector<Buff>& aBuffVectorToBuildIntoInt, std::vector<unsigned int>& aVectorToBuild)
{
	for (unsigned int iBuff = 0; iBuff < aBuffVectorToBuildIntoInt.size(); ++iBuff)
	{
		aVectorToBuild.push_back(aBuffVectorToBuildIntoInt[iBuff].GetBuffValue());
	}
}

bool Buff::CheckIfExpired(const unsigned int aTurnCount)
{
	if (myFirstRound != 0)
	{
		const unsigned int TimeDifference = aTurnCount - myFirstRound;

		if (TimeDifference > myTimer)
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
		myFirstRound = aTurnCount;

		return false;
	}
}
