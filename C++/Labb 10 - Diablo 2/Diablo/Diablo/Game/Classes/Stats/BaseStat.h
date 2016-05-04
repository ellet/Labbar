#pragma once
#include <string>
#include "BaseStatEnum.h"
#include "Buff.h"
#include <vector>

class BaseStat
{
public:
	BaseStat();
	~BaseStat();

	unsigned int GetStatValue() const;

	void TimeCheckBuffs(const unsigned int aTurnCount);

	void IncreaseStat(unsigned int aIncreaseAmount);

	void DecreaseStat(unsigned int aIncreaseAmount);

	void SetType(const enumStatTypes aStatType);

	std::string GetPrintStringOfStat() const;

	void AddMainBuff(const Buff & aBuffToAdd);

	void AddTempBuff(const Buff & aBuffToAdd);

	void SetStat(const unsigned int aValueToSet);

	unsigned int GetMainBuffCount() const;

	unsigned int GetTempBuffCount() const;

	void ClearMainBuffs();

private:
	void RemoveTempBuff(unsigned int aTempBuffIndex);

	void RecalculateValue();

	void SetStatName();

	std::string myName;

	unsigned int myValue;

	unsigned int myBaseValue;

	enumStatTypes myType;

	std::vector<Buff> myMainBuffs;
	std::vector<Buff> myTempBuffs;
};