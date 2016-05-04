#pragma once
#include "../Player/Items/ItemTypesEnum.h"
#include "BaseStatEnum.h"
#include <vector>
#include "enumVitalTypes.h"

class Buff
{
public:
	Buff();
	~Buff();

	void Initialize(unsigned int aValue, enumItemTypes aBuffType, unsigned int aTimer = 0,enumStatTypes aStatType = enumStatTypes::enumLength, enumVitalTypes aVitalType = enumVitalTypes::enumLength);

	unsigned int GetBuffValue() const;

	enumItemTypes GetBuffType() const;

	enumStatTypes GetStatType() const;

	enumVitalTypes GetVitalType() const;

	static unsigned int GetSumOfBuffVector(const std::vector<Buff> & aBuffVectorToAddUp);

	static void BuildIntVectorFromBuff(const std::vector<Buff> & aBuffVectorToBuildIntoInt, std::vector<unsigned int> & aVectorToBuild);

	bool CheckIfExpired(const unsigned int aTurnCount);

private:
	unsigned int myValue;

	enumItemTypes myBuffType;

	enumStatTypes myStatType;

	enumVitalTypes myVitalType;

	unsigned int myTimer;

	unsigned int myFirstRound;
};

